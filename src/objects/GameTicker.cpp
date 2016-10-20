#include <thread>
#include <SDL.h>
#include <atomic>
#include "GameTicker.hpp"

using namespace objects;

namespace {
  class SteadyGameTicker : public GameTicker {
    std::thread tickThread;
    std::shared_ptr<ObjectScene> scene;
    std::atomic_bool over;
    const Uint8* keyState;
  public:
    SteadyGameTicker(std::shared_ptr<ObjectScene>& _scene)
            : scene(_scene),
              over(false),
              keyState(SDL_GetKeyboardState(NULL)) {}

    virtual ~SteadyGameTicker() {}

    void run();

    virtual void start() override {
      tickThread = std::thread(std::bind(&SteadyGameTicker::run, this));
      tickThread.detach();
    }

    virtual void signalClosed() override {
      over = true;
    }

    virtual bool isOver() const override {
      return over;
    }

  private:
    void tickPlayer();
  };
}

std::shared_ptr<GameTicker> objects::createTicker(std::shared_ptr<ObjectScene>& scene) {
  return std::make_shared<SteadyGameTicker>(scene);
}

void SteadyGameTicker::run() {
  using time_point = std::chrono::time_point<std::chrono::steady_clock>;
  const time_point start = std::chrono::steady_clock::now();
  while (!over) {
    std::this_thread::sleep_for(std::chrono::milliseconds(10));

    tickPlayer();

    if (keyState[SDL_SCANCODE_ESCAPE]) {
      over = true;
    }
    if ((std::chrono::steady_clock::now() - start) >
            std::chrono::seconds(50)) {
      over = true;
    }
  }
}

void SteadyGameTicker::tickPlayer() {
  bool accelerate = keyState[SDL_SCANCODE_W];
  bool rotateLeft = keyState[SDL_SCANCODE_A];
  bool rotateRight = keyState[SDL_SCANCODE_D];
  scene->getPlayer().tick(accelerate, rotateLeft, rotateRight);
}
