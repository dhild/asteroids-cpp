#ifndef ASTEROIDS_LASERSHOT_HPP
#define ASTEROIDS_LASERSHOT_HPP

#include <glm/glm.hpp>

namespace objects {

  class Player;

  class LaserShot {
    glm::vec2 position;
    const glm::vec2 velocity;

  public:
    LaserShot(const Player& player);
    ~LaserShot();

    bool tick();

    glm::vec2 center() const {
      return position;
    }
  };

}

#endif //ASTEROIDS_LASERSHOT_HPP
