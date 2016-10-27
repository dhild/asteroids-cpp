#include <glm/gtc/type_ptr.hpp>
#include "../util.hpp"
#include "AsteroidRenderer.hpp"

using namespace asteroids;
using namespace asteroids::asteroid;

namespace {
  const float vertexData[] = {
          -0.910104f, 0.62552f,
          0.823468f, 0.793547f,
          1.06583f, 0.620735f,
          1.24281f, 0.0134702f,
          1.17241f, 0.317338f,
          0.782399f, 0.149009f,
          0.500006f, 0.579001f,
          0.136791f, 0.868943f,
          0.782133f, -0.699346f,
          0.39265f, -0.925927f,
          0.81233f, -0.119213f,
          0.880444f, -0.188565f,
          0.474873f, -0.885463f,
          0.415814f, -1.05071f,
          1.12964f, -0.394754f,
          0.181866f, -0.982547f,
          -0.52696f, -0.734211f,
          -0.225731f, -0.793479f,
          -0.0266603f, -1.04705f,
          -0.443737f, 0.952152f,
          -0.917426f, 0.453245f,
          -0.470044f, 0.779021f,
          -0.632415f, 0.692047f,
          -0.586347f, 0.617691f,
          -0.724532f, 0.465132f,
          -0.639792f, 0.437565f,
          -0.839155f, 0.390909f,
  };
  const gl::GLubyte indexData[] = {
          0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26
  };
}

AsteroidRenderer::AsteroidRenderer()
        : shader(util::loadFile("Asteroid.vert"),
                 util::loadFile("Asteroid.frag")),
          unifClipMatrix(shader.getUniformLocation("toClipMatrix")),
          vertexBufferObject(0),
          indexBufferObject(0),
          vao(0) {
  gl::glGenBuffers(1, &vertexBufferObject);
  gl::glGenBuffers(1, &indexBufferObject);
  gl::glGenVertexArrays(1, &vao);

  gl::glBindBuffer(gl::GL_ARRAY_BUFFER, vertexBufferObject);
  gl::glBufferData(gl::GL_ARRAY_BUFFER, sizeof(vertexData), vertexData, gl::GL_STATIC_DRAW);
  gl::glBindBuffer(gl::GL_ARRAY_BUFFER, 0);

  gl::glGenBuffers(1, &indexBufferObject);

  gl::glBindBuffer(gl::GL_ELEMENT_ARRAY_BUFFER, indexBufferObject);
  gl::glBufferData(gl::GL_ELEMENT_ARRAY_BUFFER, sizeof(indexData), indexData, gl::GL_STATIC_DRAW);
  gl::glBindBuffer(gl::GL_ELEMENT_ARRAY_BUFFER, 0);

  gl::glGenVertexArrays(1, &vao);
  gl::glBindVertexArray(vao);

  gl::glBindBuffer(gl::GL_ARRAY_BUFFER, vertexBufferObject);
  gl::glEnableVertexAttribArray(0);
  gl::glVertexAttribPointer(0, 2, gl::GL_FLOAT, gl::GL_FALSE, 0, 0);
  gl::glBindBuffer(gl::GL_ELEMENT_ARRAY_BUFFER, indexBufferObject);

  gl::glBindVertexArray(0);
}

AsteroidRenderer::~AsteroidRenderer() {
  if (vertexBufferObject) {
    gl::glDeleteBuffers(1, &vertexBufferObject);
  }
  if (indexBufferObject) {
    gl::glDeleteBuffers(1, &indexBufferObject);
  }
  if (vao) {
    gl::glDeleteVertexArrays(1, &vao);
  }
}

void AsteroidRenderer::render(const Asteroid& asteroid) const {
  shader.activate();
  gl::glBindVertexArray(vao);

  glm::mat4 mat = asteroid.matrix();

  gl::glUniformMatrix4fv(unifClipMatrix, 1, gl::GL_FALSE, glm::value_ptr(mat));

  gl::glDrawElements(gl::GL_TRIANGLE_FAN, 27, gl::GL_UNSIGNED_BYTE, 0);

  gl::glBindVertexArray(0);
  shader.deactivate();
}
