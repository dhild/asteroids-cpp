#ifndef ASTEROIDS_LASERSHOTRENDERER_HPP
#define ASTEROIDS_LASERSHOTRENDERER_HPP

#include "Shader.hpp"
#include "../objects/LaserShot.hpp"

namespace rendering {
  class LaserShotRenderer {
    Shader shader;
    gl::GLint unifClipMatrix;
    gl::GLint unifPointSize;
    gl::GLuint vertexBufferObject;
    gl::GLuint indexBufferObject;
    gl::GLuint vao;

  public:
    LaserShotRenderer();
    ~LaserShotRenderer();

    void draw(const objects::LaserShot& shot) const;
  };
}

#endif //ASTEROIDS_LASERSHOTRENDERER_HPP
