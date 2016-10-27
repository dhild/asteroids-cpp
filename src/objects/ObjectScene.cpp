#include <forward_list>
#include <thread>
#include <algorithm>
#include <mutex>
#include "ObjectScene.hpp"
#include "../player/DrawablePlayer.hpp"
#include "../asteroid/CircularAsteroid.hpp"

using namespace asteroids;

namespace {
  class DefaultObjectScene : public ObjectScene {
    player::DrawablePlayer gamePlayer;

    std::forward_list<std::unique_ptr<Shot>> shots;
    std::forward_list<std::unique_ptr<Asteroid>> asteroids;
    mutable std::recursive_mutex mutex;

  public:
    virtual ~DefaultObjectScene() override {}

    virtual Player& player() override {
      return gamePlayer;
    }

    virtual const Player& player() const override {
      return gamePlayer;
    }

    virtual void each_asteroid(std::function<void(const Asteroid&)> func) const override {
      std::lock_guard<std::recursive_mutex> guard(mutex);
      std::for_each(asteroids.cbegin(), asteroids.cend(), [&](const std::unique_ptr<Asteroid>& p) {
        func(*p);
      });
    }

    virtual void each_asteroid(std::function<void(Asteroid&)> func) override {
      std::lock_guard<std::recursive_mutex> guard(mutex);
      std::for_each(asteroids.cbegin(), asteroids.cend(), [&](const std::unique_ptr<Asteroid>& p) {
        func(*p);
      });
    }

    virtual void each_shot(std::function<void(const Shot&)> func) const override {
      std::lock_guard<std::recursive_mutex> guard(mutex);
      std::for_each(shots.cbegin(), shots.cend(), [&](const std::unique_ptr<Shot>& p) {
        func(*p);
      });
    }

    virtual void each_shot(std::function<void(Shot&)> func) override {
      std::lock_guard<std::recursive_mutex> guard(mutex);
      std::for_each(shots.cbegin(), shots.cend(), [&](const std::unique_ptr<Shot>& p) {
        func(*p);
      });
    }

    virtual void add_asteroid() override {
      std::lock_guard<std::recursive_mutex> guard(mutex);
      asteroids.emplace_front(std::make_unique<asteroid::CircularAsteroid>());
    }

    virtual void destroy_asteroid(const Asteroid* ast) override {
      std::lock_guard<std::recursive_mutex> guard(mutex);
      asteroids.remove_if([=](const std::unique_ptr<Asteroid>& a) { return a.get() == ast; });
    }

    virtual void add_shot() override {
      std::lock_guard<std::recursive_mutex> guard(mutex);
      shots.emplace_front(gamePlayer.create_shot());
    }

    virtual void destroy_shot(const Shot* shot) override {
      std::lock_guard<std::recursive_mutex> guard(mutex);
      shots.remove_if([=](const std::unique_ptr<Shot>& s) { return s.get() == shot; });
    }
  };
}

std::shared_ptr<ObjectScene> asteroids::create_scene() {
  return std::make_shared<DefaultObjectScene>();
}
