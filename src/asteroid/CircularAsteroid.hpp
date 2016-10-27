#ifndef ASTEROIDS_CIRCULARASTEROID_HPP
#define ASTEROIDS_CIRCULARASTEROID_HPP

#include "Asteroid.hpp"

namespace asteroids {
  namespace asteroid {

    class CircularAsteroid : public Asteroid {
      glm::vec2 position;
      float angle;
      const glm::vec2 velocity;
      const float rotation;

    public:
      CircularAsteroid();
      virtual ~CircularAsteroid();

      virtual bool tick() override;
      virtual glm::vec2 center() const override;
      virtual float size() const override;
      virtual glm::mat4 matrix() const override;
    };

  }
}

#endif //ASTEROIDS_CIRCULARASTEROID_HPP
