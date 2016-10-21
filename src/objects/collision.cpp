#include <vector>
#include "collision.hpp"

using namespace objects;

bool objects::player_collided_with_asteroid(const ObjectScene& scene) {
  std::vector<Asteroid*> close_calls;
  scene.each_asteroid([&](const Asteroid& ast) {
    glm::vec2 dist = ast.center() - scene.player().center();

  });
  return false;
}

AsteroidHit objects::shot_collided_with_asteroid(const ObjectScene& scene) {
  return objects::AsteroidHit();
}
