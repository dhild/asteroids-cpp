#ifndef ASTEROIDS_RENDERING_HPP
#define ASTEROIDS_RENDERING_HPP

#include <memory>
#include <string>
#include "objects/ObjectScene.hpp"

namespace asteroids {

  class Window {
  public:
    virtual ~Window() {};

    virtual void render(std::shared_ptr<const ObjectScene> scene) = 0;
    virtual void stop() = 0;
  };

  std::shared_ptr<Window> create_window(const char* name, int width, int height);
}

#endif //ASTEROIDS_RENDERING_HPP
