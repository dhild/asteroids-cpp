#include <random>
#include "Asteroid.hpp"
#include "GameTicker.hpp"

using namespace objects;

static const float pi = std::acos(-1.0f);
static const float velocity_bound = 0.1f / GameTicker::ticks_per_second;
static const float rotation_bound = 0.9f / GameTicker::ticks_per_second;
static const float disappear_distance = 1.2f;

static std::default_random_engine& engine() {
  static std::random_device rand_dev;
  static std::default_random_engine engine(rand_dev());
  return engine;
}

static float randomStartPos() {
  static std::uniform_real_distribution<float> uniform_dist(-disappear_distance, disappear_distance);
  return uniform_dist(engine());
}

static float randomOrientation() {
  static std::uniform_real_distribution<float> uniform_dist(-pi, pi);
  return uniform_dist(engine());
}

static float randomVelocity() {
  static std::uniform_real_distribution<float> uniform_dist(-velocity_bound, velocity_bound);
  return uniform_dist(engine());
}

static float randomRotation() {
  static std::uniform_real_distribution<float> uniform_dist(-rotation_bound, rotation_bound);
  return uniform_dist(engine());
}

Asteroid::Asteroid()
        : position(randomStartPos(), randomStartPos()),
          orientationAngle(randomOrientation()),
          velocity(randomVelocity(), randomVelocity()),
          rotationRate(randomRotation()) {}

Asteroid::~Asteroid() {
}

float Asteroid::size() const {
  return 1.2f / 20.f;
}

bool Asteroid::tick() {
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

  orientationAngle += rotationRate;
  return true;
}
