#include <random>
#include "CircularAsteroid.hpp"
#include "../objects/GameTicker.hpp"

using namespace asteroids;
using namespace asteroids::asteroid;

namespace {
  const float pi = std::acos(-1.0f);
  const float velocity_bound = 0.1f / GameTicker::ticks_per_second;
  const float rotation_bound = 0.9f / GameTicker::ticks_per_second;
  const float disappear_distance = 1.2f;

  std::default_random_engine& engine() {
    static std::random_device rand_dev;
    static std::default_random_engine engine(rand_dev());
    return engine;
  }

  float randomStartPos() {
    static std::uniform_real_distribution<float> uniform_dist(-disappear_distance, disappear_distance);
    return uniform_dist(engine());
  }

  float randomOrientation() {
    static std::uniform_real_distribution<float> uniform_dist(-pi, pi);
    return uniform_dist(engine());
  }

  float randomVelocity() {
    static std::uniform_real_distribution<float> uniform_dist(-velocity_bound, velocity_bound);
    return uniform_dist(engine());
  }

  float randomRotation() {
    static std::uniform_real_distribution<float> uniform_dist(-rotation_bound, rotation_bound);
    return uniform_dist(engine());
  }
}

CircularAsteroid::CircularAsteroid()
        : position(randomStartPos(), randomStartPos()),
          angle(randomOrientation()),
          velocity(randomVelocity(), randomVelocity()),
          rotation(randomRotation()) {}

CircularAsteroid::~CircularAsteroid() {
}

bool CircularAsteroid::tick() {
  position += velocity;
  if (position.x > disappear_distance) {
    return false;
  } else if (position.x < -disappear_distance) {
    return false;
  }
  if (position.y > disappear_distance) {
    return false;
  } else if (position.y < -disappear_distance) {
    return false;
  }

  angle += rotation;
  return true;
}

glm::mat4 CircularAsteroid::matrix() const {
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

float CircularAsteroid::size() const {
  return 1.0f / 20.0f;
}

glm::vec2 CircularAsteroid::center() const {
  return position;
}
