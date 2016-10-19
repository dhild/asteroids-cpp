#ifndef ASTEROIDS_OBJECTS_HPP
#define ASTEROIDS_OBJECTS_HPP

#include <forward_list>
#include <memory>
#include <glm/glm.hpp>

namespace objects {

  class Player {
    glm::vec2 position;
    float orientation;

  public:
    ~Player();

    glm::vec2 getCenter() const {
      return position;
    }

    float getOrientation() const {
      return orientation;
    }
  };

  class LaserShot {
  public:
    virtual ~LaserShot() {};
  };

  class Asteroid {
  public:
    virtual ~Asteroid() {};
  };

  class ObjectScene {
  public:
    virtual ~ObjectScene() {};

    static const float boardWidth;
    static const float boardHeight;

    virtual const Player& getPlayer() const = 0;

    typedef std::forward_list<LaserShot>::const_iterator LaserShot_iter;
    typedef std::forward_list<Asteroid>::const_iterator Asteroid_iter;

    virtual LaserShot_iter beginShots() const = 0;
    virtual LaserShot_iter endShots() const = 0;
    virtual Asteroid_iter beginAsteroids() const = 0;
    virtual Asteroid_iter endAsteroids() const = 0;
  };

  std::shared_ptr<ObjectScene> createScene();

}

#endif //ASTEROIDS_OBJECTS_HPP
