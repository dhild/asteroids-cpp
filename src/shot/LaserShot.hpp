#ifndef ASTEROIDS_LASERSHOT_HPP
#define ASTEROIDS_LASERSHOT_HPP

#include <glm/glm.hpp>
#include "Shot.hpp"

namespace asteroids {
  namespace shot {

    class LaserShot : public Shot {
      glm::vec2 position;
      const glm::vec2 velocity;

    public:
      LaserShot(const glm::vec2& position, const glm::vec2& velocity);

      virtual ~LaserShot();

      virtual bool tick() override;
      virtual bool check_collision(const Asteroid& asteroid) override;

      virtual glm::mat4 matrix() const override;
    };

  }
}

#endif //ASTEROIDS_LASERSHOT_HPP
