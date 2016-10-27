#ifndef ASTEROIDS_ASTEROIDRENDERER_HPP
#define ASTEROIDS_ASTEROIDRENDERER_HPP

#include <glbinding/gl/gl.h>
#include "../rendering/Shader.hpp"
#include "Asteroid.hpp"

namespace asteroids {
  namespace asteroid {

    class AsteroidRenderer {
      ::asteroids::rendering::Shader shader;
      gl::GLint unifClipMatrix;
      gl::GLuint vertexBufferObject;
      gl::GLuint indexBufferObject;
      gl::GLuint vao;

    public:
      AsteroidRenderer();
      ~AsteroidRenderer();

      void render(const Asteroid& asteroid) const;
    };

  }
}

#endif //ASTEROIDS_ASTEROIDRENDERER_HPP
