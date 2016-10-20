#ifndef ASTEROIDS_OBJECTSCENE_HPP
#define ASTEROIDS_OBJECTSCENE_HPP

#include <forward_list>
#include <memory>
#include "Asteroid.hpp"
#include "LaserShot.hpp"
#include "Player.hpp"

namespace objects {
  class ObjectScene {
  public:
    virtual ~ObjectScene() {};

    virtual Player& getPlayer() = 0;
    virtual const Player& getPlayer() const = 0;

    typedef std::forward_list<LaserShot>::iterator LaserShot_iter;
    typedef std::forward_list<Asteroid>::iterator Asteroid_iter;
    typedef std::forward_list<LaserShot>::const_iterator LaserShot_citer;
    typedef std::forward_list<Asteroid>::const_iterator Asteroid_citer;

    virtual LaserShot_citer beginShots() const = 0;
    virtual LaserShot_citer endShots() const = 0;
    virtual Asteroid_citer beginAsteroids() const = 0;
    virtual Asteroid_citer endAsteroids() const = 0;

    virtual LaserShot_iter beginShots() = 0;
    virtual LaserShot_iter endShots() = 0;
    virtual Asteroid_iter beginAsteroids() = 0;
    virtual Asteroid_iter endAsteroids() = 0;
  };

  std::shared_ptr<ObjectScene> createScene();
}

#endif //ASTEROIDS_OBJECTSCENE_HPP
