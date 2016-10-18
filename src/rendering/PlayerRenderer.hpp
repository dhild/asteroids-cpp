#ifndef ASTEROIDS_PLAYERRENDERER_HPP
#define ASTEROIDS_PLAYERRENDERER_HPP

#include "Shader.hpp"
#include "../objects.hpp"

namespace rendering {
  class PlayerRenderer {
    Shader playerShader;

  public:
    PlayerRenderer();

    void draw(const objects::Player& player) const;
  };
}

#endif //ASTEROIDS_PLAYERRENDERER_HPP
