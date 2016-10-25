#ifndef ASTEROIDS_PLAYER_HPP
#define ASTEROIDS_PLAYER_HPP

#include <glm/glm.hpp>

namespace objects {

  class Player {
    glm::vec2 position;
    float orientationAngle;
    glm::vec2 velocity;

  public:
    static const float max_velocity;

    Player();
    ~Player();

    void tick(bool accelerate, bool rotateLeft, bool rotateRight);

    float size() const;

    glm::vec2 center() const {
      return position;
    }

    float orientation() const {
      return orientationAngle;
    }
  };

}

#endif //ASTEROIDS_PLAYER_HPP
