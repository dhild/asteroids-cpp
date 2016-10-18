#include "../util.hpp"
#include "PlayerRenderer.hpp"

using namespace rendering;
using objects::Player;

PlayerRenderer::PlayerRenderer()
        : playerShader(util::loadFile("Player.vert"),
                       util::loadFile("Player.frag")) {
}

void PlayerRenderer::draw(const Player& player) const {
  glm::vec2 front = player.getFront();
  glm::vec2 backLeft = player.getBackLeft();
  glm::vec2 backRight = player.getBackRight();


}
