#include <thread>
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

    virtual LaserShot_iter beginShots() override {
      return shots.begin();
    }

    virtual LaserShot_iter endShots() override {
      return shots.end();
    }

    virtual Asteroid_iter beginAsteroids() override {
      return asteroids.begin();
    }

    virtual Asteroid_iter endAsteroids() override {
      return asteroids.end();
    }

    virtual void addAsteroid() override {
      asteroids.emplace_front();
    }

    virtual void destroyAsteroid(const Asteroid& ast) override {
      asteroids.remove_if([&ast](const Asteroid& a) { return &a == &ast; });
    }

    virtual void addShot() override {
      shots.emplace_front(player);
    }

    virtual void destroyShot(const LaserShot& shot) override {
      shots.remove_if([&shot](const LaserShot& s) { return &s == &shot; });
    }

    virtual LaserShot_citer beginShots() const override {
      return shots.cbegin();
    }

    virtual LaserShot_citer endShots() const override {
      return shots.cend();
    }

    virtual Asteroid_citer beginAsteroids() const override {
      return asteroids.cbegin();
    }

    virtual Asteroid_citer endAsteroids() const override {
      return asteroids.cend();
    }
  };
}

std::shared_ptr<ObjectScene> objects::createScene() {
  return std::make_shared<DefaultObjectScene>();
}
