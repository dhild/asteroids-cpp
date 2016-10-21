#include <cmath>
#include "LaserShot.hpp"
#include "Player.hpp"

using namespace objects;

static const float disappear_distance = 1.2f;
static const float shot_velocity_mag = Player::max_velocity * 1.1f;

static glm::vec2 shot_velocity(const Player& player) {
  glm::vec2 velocity(std::sin(player.getOrientation()),
                     std::cos(player.getOrientation()));
  float norm = std::sqrt((velocity.x * velocity.x) + (velocity.y * velocity.y));
  return velocity * (shot_velocity_mag / norm);
}

LaserShot::LaserShot(const Player& player)
        : position(player.getCenter()),
          velocity(shot_velocity(player)) {
  const float oCos = std::cos(player.getOrientation());
  const float oSin = std::sin(player.getOrientation());
  position.x += (1.0f / 20.0f) * oSin;
  position.y += (1.0f / 20.0f) * oCos;
}

LaserShot::~LaserShot() {}

bool LaserShot::tick() {
  position += velocity;
  return !(
          position.x > disappear_distance ||
          position.x < -disappear_distance ||
          position.y > disappear_distance ||
          position.y < -disappear_distance
  );
}
