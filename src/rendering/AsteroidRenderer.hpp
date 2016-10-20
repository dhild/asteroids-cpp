#ifndef ASTEROIDS_ASTEROIDRENDERER_HPP
#define ASTEROIDS_ASTEROIDRENDERER_HPP

#include "Shader.hpp"
#include "../objects/Asteroid.hpp"

namespace rendering {
  class AsteroidRenderer {
    Shader shader;
    gl::GLint unifClipMatrix;
    gl::GLuint vertexBufferObject;
    gl::GLuint indexBufferObject;
    gl::GLuint vao;

  public:
    AsteroidRenderer();
    ~AsteroidRenderer();

    void draw(const objects::Asteroid& asteroid) const;
  };
}


#endif //ASTEROIDS_ASTEROIDRENDERER_HPP
