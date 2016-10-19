#include <cmath>
#include "../objects.hpp"

using namespace objects;

Player::~Player() {}

static const float pi = std::acos(-1.0f);
//
//glm::vec2 Player::getFront() const {
//  glm::vec2 offset(std::sin(orientation), std::cos(orientation));
//  return offset + position;
//}
//
//glm::vec2 Player::getBackLeft() const {
//  static const float offset_rotation = orientation + (pi * 5.0f / 6.0f);
//  glm::vec2 offset(std::sin(offset_rotation), std::cos(offset_rotation));
//  return offset + position;
//}
//
//glm::vec2 Player::getBackRight() const {
//  static const float offset_rotation = orientation + (pi * 7.0f / 6.0f);
//  glm::vec2 offset(std::sin(offset_rotation), std::cos(offset_rotation));
//  return offset + position;
//}
