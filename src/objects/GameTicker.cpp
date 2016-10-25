#include <thread>
#include <SDL.h>
#include <atomic>
#include "GameTicker.hpp"
#include "../logging.hpp"
#include "collision.hpp"

using namespace objects;

#define TICKS_PER_SECOND_VALUE 100
const float GameTicker::ticks_per_second = TICKS_PER_SECOND_VALUE;
using tick_duration = std::chrono::duration<long, std::ratio<1, TICKS_PER_SECOND_VALUE>>;

static const std::uint64_t min_ticks_between_new_asteroids = TICKS_PER_SECOND_VALUE >> 1;
static const int desired_asteroid_count = 10;
static const std::uint64_t min_ticks_between_new_shots = TICKS_PER_SECOND_VALUE / 5;

namespace {
  class SteadyGameTicker : public GameTicker {
    std::thread tickThread;
    std::shared_ptr<ObjectScene> scene;
    std::atomic_bool over;
    const Uint8* keyState;

    unsigned long ticks_since_asteroid_added;
    unsigned long ticks_since_shot_fired;
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
    void tickAsteroids();
    void tickShots();
  };
}

std::shared_ptr<GameTicker> objects::createTicker(std::shared_ptr<ObjectScene>& scene) {
  return std::make_shared<SteadyGameTicker>(scene);
}

void SteadyGameTicker::run() {
  const auto start = std::chrono::steady_clock::now();
  ticks_since_asteroid_added = 0;
  while (!over) {
    const auto tickStart = std::chrono::steady_clock::now();

    tickPlayer();
    tickAsteroids();
    tickShots();

    if (player_collided_with_asteroid(*scene)) {
      log_info("objects.GameTicker", "Player hit by asteroid!");
    }
    const AsteroidHit check = shot_collided_with_asteroid(*scene);
    if (check.hit) {
      log_info("objects.GameTicker", "Asteroid hit by shot!");
      scene->destroy_asteroid(check.asteroid);
      scene->destroy_shot(check.laserShot);
    }

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
  scene->player().tick(accelerate, rotateLeft, rotateRight);
}

void SteadyGameTicker::tickAsteroids() {
  int numAsteroids = 0;
  {
    std::vector<Asteroid*> doomed;
    scene->each_asteroid([&](Asteroid& ast) {
      bool keep = ast.tick();
      if (!keep) {
        doomed.push_back(&ast);
      } else {
        numAsteroids++;
      }
    });
    std::for_each(doomed.cbegin(), doomed.cend(), [&](const Asteroid* a) {
      scene->destroy_asteroid(a);
    });
  }
  ++ticks_since_asteroid_added;
  if (ticks_since_asteroid_added > min_ticks_between_new_asteroids &&
      desired_asteroid_count > numAsteroids) {
    scene->add_asteroid();
    ticks_since_asteroid_added = 0;
  }
}

void SteadyGameTicker::tickShots() {
  {
    std::vector<LaserShot*> doomed;
    scene->each_shot([&](LaserShot& shot) {
      bool keep = shot.tick();
      if (!keep) {
        doomed.push_back(&shot);
      }
    });
    std::for_each(doomed.cbegin(), doomed.cend(), [&](const LaserShot* l) {
      scene->destroy_shot(l);
    });
  }
  ++ticks_since_shot_fired;
  if (keyState[SDL_SCANCODE_SPACE] &&
      ticks_since_shot_fired > min_ticks_between_new_shots) {
    scene->add_shot();
    ticks_since_shot_fired = 0;
  }
}
