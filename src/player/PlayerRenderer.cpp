#include <glm/gtc/type_ptr.hpp>
#include "../logging.hpp"
#include "../util.hpp"
#include "DrawablePlayer.hpp"
#include "PlayerRenderer.hpp"

using namespace asteroids;
using namespace asteroids::player;

namespace {
  const float vertexData[] = {
          DrawablePlayer::point_front.x, DrawablePlayer::point_front.y,
          DrawablePlayer::point_right.x, DrawablePlayer::point_right.y,
          DrawablePlayer::point_left.x, DrawablePlayer::point_left.y
  };
  const gl::GLubyte indexData[] = {
          0, 1, 2
  };
}

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

void PlayerRenderer::render(const Player& player) const {
  playerShader.activate();
  gl::glBindVertexArray(vao);

  glm::mat4 mat = player.matrix();

  gl::glUniformMatrix4fv(unifClipMatrix, 1, gl::GL_FALSE, glm::value_ptr(mat));

  gl::glDrawElements(gl::GL_TRIANGLES, 3, gl::GL_UNSIGNED_BYTE, 0);

  gl::glBindVertexArray(0);
  playerShader.deactivate();
}
