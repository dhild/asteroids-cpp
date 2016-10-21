#include <glbinding/gl/gl.h>
#include <glm/gtc/type_ptr.hpp>
#include "../util.hpp"
#include "PlayerRenderer.hpp"

using namespace rendering;
using objects::Player;

static const float vertexData[] = {
        0.0f, 1.0f,
        0.5f, -1.0f,
        -0.5f, -1.0f
};
static const gl::GLubyte indexData[] = {
        0, 1, 2
};

PlayerRenderer::PlayerRenderer()
        : playerShader(util::loadFile("Player.vert"),
                       util::loadFile("Player.frag")),
          unifClipMatrix(playerShader.getUniformLocation("toClipMatrix")),
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

PlayerRenderer::~PlayerRenderer() {
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

void PlayerRenderer::draw(const Player& player) const {
  playerShader.activate();
  gl::glBindVertexArray(vao);

  glm::vec2 pos = player.center();
  float orientation = player.orientation();

  glm::mat4 mat(1.0f);

  // Translate
  mat[3].x = pos.x;
  mat[3].y = pos.y;

  // Scale
  glm::mat4 tmp(1.0f);
  float scale = 1.0f / 20.0f;
  tmp[0].x *= scale;
  tmp[1].y *= scale;
  mat *= tmp;

  // Rotate
  tmp = glm::mat4(1.0f);
  float oCos = std::cos(-orientation);
  float oSin = std::sin(-orientation);
  tmp[0].x *= oCos;
  tmp[0].y = oSin;
  tmp[1].x = -oSin;
  tmp[1].y *= oCos;
  mat *= tmp;

  gl::glUniformMatrix4fv(unifClipMatrix, 1, gl::GL_FALSE, glm::value_ptr(mat));

  gl::glDrawElements(gl::GL_TRIANGLES, 3, gl::GL_UNSIGNED_BYTE, 0);

  gl::glBindVertexArray(0);
  playerShader.deactivate();
}
