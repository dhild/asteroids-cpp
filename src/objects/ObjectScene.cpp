#include <forward_list>
#include <thread>
#include <algorithm>
#include <mutex>
#include "ObjectScene.hpp"

using namespace objects;

namespace {
  class DefaultObjectScene : public ObjectScene {
    Player gamePlayer;

    std::forward_list<LaserShot> shots;
    std::forward_list<Asteroid> asteroids;
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
      std::for_each(asteroids.cbegin(), asteroids.cend(), func);
    }

    virtual void each_asteroid(std::function<void(Asteroid&)> func) override {
      std::lock_guard<std::recursive_mutex> guard(mutex);
      std::for_each(asteroids.begin(), asteroids.end(), func);
    }

    virtual void each_shot(std::function<void(const LaserShot&)> func) const override {
      std::lock_guard<std::recursive_mutex> guard(mutex);
      std::for_each(shots.cbegin(), shots.cend(), func);
    }

    virtual void each_shot(std::function<void(LaserShot&)> func) override {
      std::lock_guard<std::recursive_mutex> guard(mutex);
      std::for_each(shots.begin(), shots.end(), func);
    }

    virtual void add_asteroid() override {
      std::lock_guard<std::recursive_mutex> guard(mutex);
      asteroids.emplace_front();
    }

    virtual void destroy_asteroid(const Asteroid* ast) override {
      std::lock_guard<std::recursive_mutex> guard(mutex);
      asteroids.remove_if([=](const Asteroid& a) { return &a == ast; });
    }

    virtual void add_shot() override {
      std::lock_guard<std::recursive_mutex> guard(mutex);
      shots.emplace_front(gamePlayer);
    }

    virtual void destroy_shot(const LaserShot* shot) override {
      std::lock_guard<std::recursive_mutex> guard(mutex);
      shots.remove_if([=](const LaserShot& s) { return &s == shot; });
    }
  };
}

std::shared_ptr<ObjectScene> objects::create_scene() {
  return std::make_shared<DefaultObjectScene>();
}
