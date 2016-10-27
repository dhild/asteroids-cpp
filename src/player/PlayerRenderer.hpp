#ifndef ASTEROIDS_PLAYERRENDERER_HPP
#define ASTEROIDS_PLAYERRENDERER_HPP

#include <glbinding/gl/gl.h>
#include "../rendering/Shader.hpp"
#include "Player.hpp"

namespace asteroids {
  namespace player {

    class PlayerRenderer {
      ::asteroids::rendering::Shader playerShader;
      gl::GLint unifClipMatrix;
      gl::GLuint vertexBufferObject;
      gl::GLuint indexBufferObject;
      gl::GLuint vao;

    public:
      PlayerRenderer();
      ~PlayerRenderer();

      void render(const Player& player) const;
    };

  }
}

#endif //ASTEROIDS_PLAYERRENDERER_HPP
