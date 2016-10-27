#include <cmath>
#include "../logging.hpp"
#include "../objects/GameTicker.hpp"
#include "DrawablePlayer.hpp"
#include "../shot/LaserShot.hpp"

using namespace ::asteroids;
using namespace ::asteroids::player;

namespace {
  const float pi = std::acos(-1.0f);
  const float max_velocity = 2.0f / GameTicker::ticks_per_second;
  const float max_velocity_squared = max_velocity * max_velocity;
  const float rotation_rate = 1.0f / GameTicker::ticks_per_second;
  const float acceleration_rate = 0.04f / GameTicker::ticks_per_second;
  const float deceleration_rate = 1.0f - (1.0f / GameTicker::ticks_per_second);
}

const glm::vec2 DrawablePlayer::point_front(0.0f, 1.0f);
const glm::vec2 DrawablePlayer::point_right(0.5f, -1.0f);
const glm::vec2 DrawablePlayer::point_left(-0.5f, -1.0f);

float Player::max_velocity() {
  return ::max_velocity;
}

std::unique_ptr<Shot> DrawablePlayer::create_shot() const {
  glm::mat4 mat = matrix();
  glm::vec4 position4(point_front.x, point_front.y, 0.0, 1.0);
  position4 = mat * position4;
  glm::vec2 position(position4.x, position4.y);

  glm::vec2 velocity(std::sin(angle), std::cos(angle));
  float norm = std::sqrt((velocity.x * velocity.x) + (velocity.y * velocity.y));
  velocity /= norm;

  return std::make_unique<shot::LaserShot>(position, velocity);
}

void DrawablePlayer::tick(bool accelerate, bool rotateLeft, bool rotateRight) {
  if (accelerate) {
    glm::vec2 acc;
    acc.x = std::sin(angle);
    acc.y = std::cos(angle);
    acc *= acceleration_rate;
    velocity += acc;
    float mag2 = (velocity.x * velocity.x) + (velocity.y * velocity.y);
    if (mag2 > max_velocity_squared) {
      velocity *= max_velocity_squared / mag2;
      log_debug("DrawablePlayer", "Exceeded maximum velocity");
    }
  } else {
    velocity *= deceleration_rate;
  }

  center += velocity;
  if (center.x > 1.0f) {
    center.x = -1.0f;
  } else if (center.x < -1.0f) {
    center.x = 1.0f;
  }
  if (center.y > 1.0f) {
    center.y = -1.0f;
  } else if (center.y < -1.0f) {
    center.y = 1.0f;
  }

  if (rotateLeft ^ rotateRight) {
    if (rotateLeft) {
      angle -= (pi * rotation_rate);
    } else {
      angle += (pi * rotation_rate);
    }
  }
}

glm::mat4 DrawablePlayer::matrix() const {
  glm::mat4 mat(1.0f);

  // Translate
  mat[3].x = center.x;
  mat[3].y = center.y;

  // Scale
  glm::mat4 tmp(1.0f);
  float scale = 1.0f / 20.0f;
  tmp[0].x *= scale;
  tmp[1].y *= scale;
  mat *= tmp;

  // Rotate
  tmp = glm::mat4(1.0f);
  float oCos = std::cos(-angle);
  float oSin = std::sin(-angle);
  tmp[0].x *= oCos;
  tmp[0].y = oSin;
  tmp[1].x = -oSin;
  tmp[1].y *= oCos;
  mat *= tmp;

  return mat;
}

bool DrawablePlayer::check_collision(const Asteroid& asteroid) {
  // TODO: Temp check is just asteroid close to player.
  glm::vec2 distanceV = asteroid.center() - center;
  float distance = std::sqrt((distanceV.x * distanceV.x) + (distanceV.y * distanceV.y));
  return distance < (asteroid.size() + 1.5f);
}
