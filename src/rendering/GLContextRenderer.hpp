#ifndef ASTEROIDS_GLCONTEXTRENDERER_HPP
#define ASTEROIDS_GLCONTEXTRENDERER_HPP

#include <atomic>
#include <memory>
#include <SDL.h>

#include "../rendering.hpp"

namespace asteroids {
  namespace rendering {

    class WindowRenderer {
    public:
      virtual ~WindowRenderer() {}

      virtual void resized(int width, int height) const = 0;
      virtual void draw(const ObjectScene& scene) const = 0;
    };

    std::unique_ptr<WindowRenderer> create_renderer(SDL_Window* window);
  }
}

#endif //ASTEROIDS_GLCONTEXTRENDERER_HPP
