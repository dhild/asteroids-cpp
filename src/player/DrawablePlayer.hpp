#ifndef ASTEROIDS_DRAWABLEPLAYER_HPP
#define ASTEROIDS_DRAWABLEPLAYER_HPP

#include "Player.hpp"

namespace asteroids {
  namespace player {
    class DrawablePlayer : public Player {
      glm::vec2 center;
      float angle;
      glm::vec2 velocity;

    public:
      DrawablePlayer() : center(0, 0), angle(0), velocity(0, 0) {}

      virtual ~DrawablePlayer() {}

      virtual std::unique_ptr<Shot> create_shot() const override;
      virtual bool check_collision(const Asteroid& asteroid) override;

      virtual void tick(bool accelerate, bool rotateLeft, bool rotateRight) override;

      virtual glm::mat4 matrix() const override;

      static const glm::vec2 point_front;
      static const glm::vec2 point_right;
      static const glm::vec2 point_left;
    };
  }
}

#endif //ASTEROIDS_DRAWABLEPLAYER_HPP
