#ifndef ASTEROIDS_PLAYERRENDERER_HPP
#define ASTEROIDS_PLAYERRENDERER_HPP

#include "Shader.hpp"
#include "../objects.hpp"

namespace rendering {
  class PlayerRenderer {
    Shader playerShader;
    gl::GLint unifClipMatrix;
    gl::GLuint vertexBufferObject;
    gl::GLuint indexBufferObject;
    gl::GLuint vao;

  public:
    PlayerRenderer();
    ~PlayerRenderer();

    void draw(const objects::Player& player) const;
  };
}

#endif //ASTEROIDS_PLAYERRENDERER_HPP
