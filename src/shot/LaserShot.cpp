#include "LaserShot.hpp"
#include "../player/Player.hpp"

using namespace ::asteroids;
using namespace ::asteroids::shot;

namespace {
  const float disappear_distance = 1.2f;
  const float shot_velocity_mag = Player::max_velocity() * 1.1f;
}

LaserShot::LaserShot(const glm::vec2& _position, const glm::vec2& _velocity)
        : position(_position), velocity(_velocity * shot_velocity_mag) {}

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

glm::mat4 LaserShot::matrix() const {
  glm::mat4 mat(1.0f);

  // Translate
  mat[3].x = position.x;
  mat[3].y = position.y;

  // Scale
  glm::mat4 tmp(1.0f);
  float scale = 1.0f / 20.0f;
  tmp[0].x *= scale;
  tmp[1].y *= scale;
  mat *= tmp;

  return mat;
}

bool LaserShot::check_collision(const Asteroid& asteroid) {
  glm::vec2 distanceV = position - asteroid.center();
  float distance = std::sqrt((distanceV.x * distanceV.x) + (distanceV.y * distanceV.y));
  return distance < asteroid.size();
}
