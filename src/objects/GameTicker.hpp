#ifndef ASTEROIDS_GAMETICKER_HPP
#define ASTEROIDS_GAMETICKER_HPP

#include "ObjectScene.hpp"

namespace objects {
  class GameTicker {
  public:
    virtual ~GameTicker() {};

    virtual void start() = 0;
    virtual void signalClosed() = 0;
    virtual bool isOver() const = 0;

    static const float ticks_per_second;
  };

  std::shared_ptr<GameTicker> createTicker(std::shared_ptr<ObjectScene>& scene);
}

#endif //ASTEROIDS_GAMETICKER_HPP
