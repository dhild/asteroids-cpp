#ifndef ASTEROIDS_RENDERING_HPP
#define ASTEROIDS_RENDERING_HPP

#include <memory>
#include "objects.hpp"

namespace rendering {

  class Window {
  public:
    virtual ~Window() {};

    virtual void render(std::shared_ptr<const objects::ObjectScene> scene) = 0;
    virtual void stop() = 0;
  };

  std::shared_ptr<Window> createWindow(const char* name, int width = 1280, int height = 720);
}

#endif //ASTEROIDS_RENDERING_HPP
