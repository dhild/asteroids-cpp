#ifndef ASTEROIDS_GAME_HPP
#define ASTEROIDS_GAME_HPP

#include "rendering.hpp"

namespace asteroids {
  class Game {
    std::shared_ptr<asteroids::Window> window;

  public:
    explicit Game(const char* title);
    ~Game();

    void run();
  };
}

#endif //ASTEROIDS_GAME_HPP
