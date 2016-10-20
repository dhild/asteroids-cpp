#include <cmath>
#include "../logging.hpp"
#include "Player.hpp"
#include "GameTicker.hpp"

using namespace objects;

static const float pi = std::acos(-1.0f);
static const float max_velocity_squared = 0.3333f / GameTicker::ticks_per_second;
static const float rotation_rate = 0.9f / GameTicker::ticks_per_second;
static const float acceleration_rate = 0.05f / GameTicker::ticks_per_second;
static const float deceleration_rate = 1.0f - (1.0f / GameTicker::ticks_per_second);

Player::Player() : position(0, 0), orientation(0), velocity(0, 0) {}

Player::~Player() {}

void Player::tick(bool accelerate, bool rotateLeft, bool rotateRight) {
  if (accelerate) {
    glm::vec2 acc;
    acc.x = std::sin(orientation);
    acc.y = std::cos(orientation);
    acc *= acceleration_rate;
    velocity += acc;
    float mag2 = (velocity.x * velocity.x) + (velocity.y * velocity.y);
    if (mag2 > max_velocity_squared) {
      velocity *= max_velocity_squared / mag2;
      log_debug("Player", "Exceeded maximum velocity");
    }
  } else {
    velocity *= deceleration_rate;
  }

  position += velocity;
  if (position.x > 1.0f) {
    position.x = -1.0f;
  } else if (position.x < -1.0f) {
    position.x = 1.0f;
  }
  if (position.y > 1.0f) {
    position.y = -1.0f;
  } else if (position.y < -1.0f) {
    position.y = 1.0f;
  }

  if (rotateLeft ^ rotateRight) {
    if (rotateLeft) {
      orientation -= (pi * rotation_rate);
    } else {
      orientation += (pi * rotation_rate);
    }
  }
}
