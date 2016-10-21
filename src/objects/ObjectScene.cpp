#include <forward_list>
#include <thread>
#include <algorithm>
#include "ObjectScene.hpp"

using namespace objects;

namespace {
  class DefaultObjectScene : public ObjectScene {
    Player player;

    std::forward_list<LaserShot> shots;
    std::forward_list<Asteroid> asteroids;

  public:
    virtual ~DefaultObjectScene() override {}

    virtual Player& getPlayer() override {
      return player;
    }

    virtual const Player& getPlayer() const override {
      return player;
    }

    virtual void each_asteroid(std::function<void(const Asteroid&)> func) const override {
      std::for_each(asteroids.cbegin(), asteroids.cend(), func);
    }

    virtual void each_asteroid(std::function<void(Asteroid&)> func) override {
      std::for_each(asteroids.begin(), asteroids.end(), func);
    }

    virtual void each_shot(std::function<void(const LaserShot&)> func) const override {
      std::for_each(shots.cbegin(), shots.cend(), func);
    }

    virtual void each_shot(std::function<void(LaserShot&)> func) override {
      std::for_each(shots.begin(), shots.end(), func);
    }

    virtual void addAsteroid() override {
      asteroids.emplace_front();
    }

    virtual void destroyAsteroid(const Asteroid* ast) override {
      asteroids.remove_if([=](const Asteroid& a) { return &a == ast; });
    }

    virtual void addShot() override {
      shots.emplace_front(player);
    }

    virtual void destroyShot(const LaserShot* shot) override {
      shots.remove_if([=](const LaserShot& s) { return &s == shot; });
    }
  };
}

std::shared_ptr<ObjectScene> objects::createScene() {
  return std::make_shared<DefaultObjectScene>();
}
