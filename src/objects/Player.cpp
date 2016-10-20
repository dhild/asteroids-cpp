#include <cmath>
#include <Poco/Logger.h>
#include "Player.hpp"

using namespace objects;

static const float pi = std::acos(-1.0f);
static const float MAX_VELOCITY_SQUARED = 0.003f;

Player::Player() : position(0, 0), orientation(0), velocity(0, 0) {}

Player::~Player() {}

void Player::tick(bool accelerate, bool rotateLeft, bool rotateRight) {
  if (accelerate) {
    glm::vec2 acc;
    acc.x = std::sin(orientation);
    acc.y = std::cos(orientation);
    acc *= 0.0005;
    velocity += acc;
    float mag2 = (velocity.x * velocity.x) + (velocity.y * velocity.y);
    if (mag2 > MAX_VELOCITY_SQUARED) {
      velocity *= MAX_VELOCITY_SQUARED / mag2;
      static Poco::Logger& logger = Poco::Logger::get("Player");
      logger.debug("Exceeded maximum velocity");
    }
  } else {
    velocity *= 0.99f;
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
      orientation -= (pi * 0.009);
    } else {
      orientation += (pi * 0.009);
    }
  }
}
