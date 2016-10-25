#ifndef ASTEROIDS_ASTEROID_HPP
#define ASTEROIDS_ASTEROID_HPP

#include <glm/glm.hpp>

namespace objects {

  class Asteroid {
    glm::vec2 position;
    float orientationAngle;
    const glm::vec2 velocity;
    const float rotationRate;

  public:
    Asteroid();
    ~Asteroid();

    bool tick();

    float size() const;

    glm::vec2 center() const {
      return position;
    }

    float orientation() const {
      return orientationAngle;
    }
  };

}


#endif //ASTEROIDS_ASTEROID_HPP
