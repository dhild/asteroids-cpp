#ifndef ASTEROIDS_PLAYER_HPP
#define ASTEROIDS_PLAYER_HPP

#include <glm/glm.hpp>

namespace objects {

  class Player {
    glm::vec2 position;
    float orientation;
    glm::vec2 velocity;

  public:
    static const float max_velocity;

    Player();
    ~Player();

    void tick(bool accelerate, bool rotateLeft, bool rotateRight);

    glm::vec2 getCenter() const {
      return position;
    }

    float getOrientation() const {
      return orientation;
    }
  };

}

#endif //ASTEROIDS_PLAYER_HPP
