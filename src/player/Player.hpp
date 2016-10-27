#ifndef ASTEROIDS_PLAYER_HPP
#define ASTEROIDS_PLAYER_HPP

#include <memory>
#include <glm/glm.hpp>
#include "../shot/Shot.hpp"

namespace asteroids {

  class Player {
  public:
    static float max_velocity();

    virtual ~Player() {}

    virtual void tick(bool accelerate, bool rotateLeft, bool rotateRight) = 0;
    virtual glm::mat4 matrix() const = 0;

    virtual std::unique_ptr<Shot> create_shot() const = 0;

    virtual bool check_collision(const Asteroid& asteroid) = 0;
  };

}

#endif //ASTEROIDS_PLAYER_HPP
