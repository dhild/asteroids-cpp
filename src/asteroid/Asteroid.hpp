#ifndef ASTEROIDS_ASTEROID_HPP
#define ASTEROIDS_ASTEROID_HPP

#include <glm/glm.hpp>

namespace asteroids {

  class Asteroid {
  public:
    virtual ~Asteroid() {}

    virtual bool tick() = 0;
    virtual glm::vec2 center() const = 0;
    virtual glm::mat4 matrix() const = 0;
    virtual float size() const = 0;
  };

}


#endif //ASTEROIDS_ASTEROID_HPP
