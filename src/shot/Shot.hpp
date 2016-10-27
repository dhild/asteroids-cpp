#ifndef ASTEROIDS_SHOT_HPP
#define ASTEROIDS_SHOT_HPP

#include <glm/glm.hpp>
#include "../asteroid/Asteroid.hpp"

namespace asteroids {

  class Shot {
  public:
    virtual ~Shot() {}

    virtual bool tick() = 0;
    virtual glm::mat4 matrix() const = 0;

    virtual bool check_collision(const Asteroid& asteroid) = 0;
  };

}

#endif //ASTEROIDS_SHOT_HPP
