#ifndef ASTEROIDS_RENDERING_HPP
#define ASTEROIDS_RENDERING_HPP

#include <memory>
#include <string>
#include "objects/ObjectScene.hpp"

namespace rendering {

  class TextOverlay {
  public:
    virtual ~TextOverlay() {}

    virtual void update(const std::string& newText) = 0;
  };

  class Window {
  public:
    virtual ~Window() {};

    virtual void render(std::shared_ptr<const objects::ObjectScene> scene) = 0;
    virtual void stop() = 0;

    virtual std::shared_ptr<TextOverlay> textOverlay() = 0;
  };

  std::shared_ptr<Window> createWindow(const char* name, int width, int height);
}

#endif //ASTEROIDS_RENDERING_HPP
