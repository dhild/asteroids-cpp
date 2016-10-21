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

    virtual Player& player() = 0;
    virtual const Player& player() const = 0;

    virtual void each_asteroid(std::function<void(const Asteroid&)> func) const = 0;
    virtual void each_asteroid(std::function<void(Asteroid&)> func) = 0;
    virtual void each_shot(std::function<void(const LaserShot&)> func) const = 0;
    virtual void each_shot(std::function<void(LaserShot&)> func) = 0;

    virtual void add_asteroid() = 0;
    virtual void destroy_asteroid(const Asteroid* ast) = 0;
    virtual void add_shot() = 0;
    virtual void destroy_shot(const LaserShot* shot) = 0;
  };

  std::shared_ptr<ObjectScene> create_scene();
}

#endif //ASTEROIDS_OBJECTSCENE_HPP
