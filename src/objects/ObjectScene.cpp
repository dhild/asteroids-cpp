#include "../objects.hpp"

using namespace objects;

namespace {
  class DefaultObjectScene : public ObjectScene {
    Player player;

    std::forward_list<LaserShot> shots;
    std::forward_list<Asteroid> asteroids;

  public:
    virtual ~DefaultObjectScene() override {}

    virtual const Player& getPlayer() const override {
      return player;
    }

    virtual std::forward_list<LaserShot>::const_iterator beginShots() const override {
      return shots.cbegin();
    }

    virtual std::forward_list<LaserShot>::const_iterator endShots() const override {
      return shots.cend();
    }

    virtual std::forward_list<Asteroid>::const_iterator beginAsteroids() const override {
      return asteroids.cbegin();
    }

    virtual std::forward_list<Asteroid>::const_iterator endAsteroids() const override {
      return asteroids.cend();
    }
  };
}

const float ObjectScene::boardWidth = 500;
const float ObjectScene::boardHeight = ObjectScene::boardWidth;

std::shared_ptr<ObjectScene> objects::createScene() {
  return std::make_shared<DefaultObjectScene>();
}
