#ifndef ASTEROIDS_OBJECTSCENE_HPP
#define ASTEROIDS_OBJECTSCENE_HPP

#include <memory>
#include "Asteroid.hpp"
#include "LaserShot.hpp"
#include "Player.hpp"

namespace objects {
  class ObjectScene {
  public:
    virtual ~ObjectScene() {};

    virtual Player& getPlayer() = 0;
    virtual const Player& getPlayer() const = 0;

    virtual void each_asteroid(std::function<void(const Asteroid&)> func) const = 0;
    virtual void each_asteroid(std::function<void(Asteroid&)> func) = 0;
    virtual void each_shot(std::function<void(const LaserShot&)> func) const = 0;
    virtual void each_shot(std::function<void(LaserShot&)> func) = 0;

    virtual void addAsteroid() = 0;
    virtual void destroyAsteroid(const Asteroid* ast) = 0;
    virtual void addShot() = 0;
    virtual void destroyShot(const LaserShot* shot) = 0;
  };

  std::shared_ptr<ObjectScene> createScene();
}

#endif //ASTEROIDS_OBJECTSCENE_HPP
