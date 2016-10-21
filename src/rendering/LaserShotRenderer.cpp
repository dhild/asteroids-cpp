#include <glbinding/gl/gl.h>
#include <glm/gtc/type_ptr.hpp>
#include "../util.hpp"
#include "LaserShotRenderer.hpp"

using namespace rendering;
using objects::LaserShot;

static const float vertexData[] = {
        0.0f, 0.0f
};
static const gl::GLubyte indexData[] = {
        0
};

rendering::LaserShotRenderer::LaserShotRenderer()
        : shader(util::loadFile("Shot.vert"),
                 util::loadFile("Player.frag")),
          unifClipMatrix(shader.getUniformLocation("toClipMatrix")),
          unifPointSize(shader.getUniformLocation("pointSize")),
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

  gl::glEnable(gl::GL_PROGRAM_POINT_SIZE);
}

rendering::LaserShotRenderer::~LaserShotRenderer() {
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

void rendering::LaserShotRenderer::draw(const LaserShot& shot) const {
  shader.activate();
  gl::glBindVertexArray(vao);

  glm::vec2 pos = shot.center();

  glm::mat4 mat(1.0f);

  // Translate
  mat[3].x = pos.x;
  mat[3].y = pos.y;

  gl::glUniform1f(unifPointSize, 5.0f);
  gl::glUniformMatrix4fv(unifClipMatrix, 1, gl::GL_FALSE, glm::value_ptr(mat));

  gl::glDrawElements(gl::GL_POINTS, 1, gl::GL_UNSIGNED_BYTE, 0);

  gl::glBindVertexArray(0);
  shader.deactivate();
}
