#ifndef ASTEROIDS_ASTEROID_HPP
#define ASTEROIDS_ASTEROID_HPP

#include <glm/glm.hpp>

namespace objects {

  class Asteroid {
    glm::vec2 position;
    float orientation;
    const glm::vec2 velocity;
    const float rotationRate;

  public:
    Asteroid();
    ~Asteroid();

    bool tick();

    glm::vec2 getCenter() const {
      return position;
    }

    float getOrientation() const {
      return orientation;
    }
  };

}


#endif //ASTEROIDS_ASTEROID_HPP
