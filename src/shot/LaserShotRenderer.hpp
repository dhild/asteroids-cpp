#ifndef ASTEROIDS_LASERSHOTRENDERER_HPP
#define ASTEROIDS_LASERSHOTRENDERER_HPP

#include <glbinding/gl/gl.h>
#include "../rendering/Shader.hpp"
#include "LaserShot.hpp"

namespace asteroids {
  namespace shot {

    class LaserShotRenderer {
      ::asteroids::rendering::Shader shader;
      gl::GLint unifClipMatrix;
      gl::GLint unifPointSize;
      gl::GLuint vertexBufferObject;
      gl::GLuint indexBufferObject;
      gl::GLuint vao;

    public:
      LaserShotRenderer();
      ~LaserShotRenderer();

      void render(const Shot& shot) const;
    };

  }
}

#endif //ASTEROIDS_LASERSHOTRENDERER_HPP
