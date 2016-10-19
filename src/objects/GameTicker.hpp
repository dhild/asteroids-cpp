#ifndef ASTEROIDS_GAMETICKER_HPP
#define ASTEROIDS_GAMETICKER_HPP

#include "../objects.hpp"

namespace objects {
  class GameTicker {
  public:
    virtual ~GameTicker() {};

    virtual void start() = 0;
    virtual bool isOver() const = 0;
  };

  std::shared_ptr<GameTicker> createTicker(std::shared_ptr<ObjectScene>& scene);
}

#endif //ASTEROIDS_GAMETICKER_HPP
