#include <thread>
#include <SDL.h>
#include <atomic>
#include "GameTicker.hpp"
#include "../logging.hpp"

using namespace objects;

#define TICKS_PER_SECOND_VALUE 100
const float GameTicker::ticks_per_second = TICKS_PER_SECOND_VALUE;
using tick_duration = std::chrono::duration<long, std::ratio<1, TICKS_PER_SECOND_VALUE>>;

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
  const auto start = std::chrono::steady_clock::now();
  while (!over) {
    const auto tickStart = std::chrono::steady_clock::now();

    tickPlayer();

    if (keyState[SDL_SCANCODE_ESCAPE]) {
      over = true;
    }
    if ((std::chrono::steady_clock::now() - start) >
            std::chrono::seconds(50)) {
      over = true;
    }
    const auto elapsed = std::chrono::steady_clock::now() - tickStart;
    const auto remaining = tick_duration(1) - elapsed;
    if (remaining > std::chrono::nanoseconds(50)) {
      std::this_thread::sleep_for(remaining);
    }
  }
}

void SteadyGameTicker::tickPlayer() {
  bool accelerate = keyState[SDL_SCANCODE_W];
  bool rotateLeft = keyState[SDL_SCANCODE_A];
  bool rotateRight = keyState[SDL_SCANCODE_D];
  scene->getPlayer().tick(accelerate, rotateLeft, rotateRight);
}
