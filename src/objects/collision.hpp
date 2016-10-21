#ifndef ASTEROIDS_COLLISION_HPP
#define ASTEROIDS_COLLISION_HPP

#include "ObjectScene.hpp"

namespace objects {

  bool player_collided_with_asteroid(const ObjectScene& scene);

  class AsteroidHit {
  public:
    AsteroidHit() : hit(false), asteroid(nullptr), laserShot(nullptr) {}
    AsteroidHit(const Asteroid* ast, const LaserShot* shot)
            :hit(true), asteroid(ast), laserShot(shot) {}

    bool hit;
    const Asteroid* asteroid;
    const LaserShot* laserShot;
  };

  AsteroidHit shot_collided_with_asteroid(const ObjectScene& scene);

}
#endif //ASTEROIDS_COLLISION_HPP
