#include <random>
#include "Asteroid.hpp"
#include "GameTicker.hpp"

using namespace objects;

static const float pi = std::acos(-1.0f);
static const float velocity_bound = 0.1f / GameTicker::ticks_per_second;
static const float rotation_bound = 0.9f / GameTicker::ticks_per_second;

static std::default_random_engine& engine() {
  static std::random_device rand_dev;
  static std::default_random_engine engine(rand_dev());
  return engine;
}

static float randomStartPos() {
  static std::uniform_real_distribution<float> uniform_dist(-1, 1);
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
          orientation(randomOrientation()),
          velocity(randomVelocity(), randomVelocity()),
          rotationRate(randomRotation()) {}

Asteroid::~Asteroid() {
}

void Asteroid::tick() {
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

  orientation += rotationRate;
}
