#include <vector>
#include <algorithm>
#include "collision.hpp"

using namespace objects;

bool objects::player_collided_with_asteroid(const ObjectScene& scene) {
  std::vector<const Asteroid*> close_calls;
  const Player& player = scene.player();
  scene.each_asteroid([&](const Asteroid& ast) {
    glm::vec2 distanceV = ast.center() - player.center();
    float distance = std::sqrt((distanceV.x * distanceV.x) + (distanceV.y * distanceV.y));
    if (distance < (ast.size() + player.size())) {
      close_calls.push_back(&ast);
    }
  });

  return std::any_of(close_calls.cbegin(), close_calls.cend(), [&](const Asteroid* ast) -> bool {
    // TODO: Temp check is just asteroid close to player.
    return true;
  });
}

AsteroidHit objects::shot_collided_with_asteroid(const ObjectScene& scene) {
  AsteroidHit hit;
  scene.each_shot([&](const LaserShot& shot) {
    scene.each_asteroid([&](const Asteroid& ast) {
      glm::vec2 distanceV = shot.center() - ast.center();
      float distance = std::sqrt((distanceV.x * distanceV.x) + (distanceV.y * distanceV.y));
      if (distance < ast.size()) {
        hit = AsteroidHit(&ast, &shot);
      }
    });
  });
  return hit;
}
