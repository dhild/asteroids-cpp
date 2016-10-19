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
  public:
    SteadyGameTicker(std::shared_ptr<ObjectScene>& _scene) : scene(_scene) {
      over = false;
    }

    virtual ~SteadyGameTicker() {}

    void run();

    virtual void start() override {
      tickThread = std::thread(std::bind(&SteadyGameTicker::run, this));
      tickThread.detach();
    }

    virtual bool isOver() const override {
      return over;
    }
  };
}

std::shared_ptr<GameTicker> objects::createTicker(std::shared_ptr<ObjectScene>& scene) {
  return std::make_shared<SteadyGameTicker>(scene);
}

void SteadyGameTicker::run() {
  const Uint8* keyState = SDL_GetKeyboardState(NULL);
  using time_point = std::chrono::time_point<std::chrono::steady_clock>;
  const time_point start = std::chrono::steady_clock::now();
  time_point last = start;
  while (!over) {
    std::this_thread::sleep_for(std::chrono::milliseconds(10));

    scene->getPlayer().tick(keyState[SDL_SCANCODE_W], keyState[SDL_SCANCODE_A], keyState[SDL_SCANCODE_D]);

    over = (bool) (keyState[SDL_SCANCODE_ESCAPE]);
  }
}
