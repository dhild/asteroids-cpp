#ifndef ASTEROIDS_GLCONTEXTRENDERER_HPP
#define ASTEROIDS_GLCONTEXTRENDERER_HPP

#include <atomic>
#include <memory>
#include <SDL.h>

#include "../rendering.hpp"

namespace rendering {

  void run_render_loop(SDL_Window* window,
                       std::shared_ptr<const objects::ObjectScene> scene,
                       std::shared_ptr<std::atomic_bool> running_flag);

}

#endif //ASTEROIDS_GLCONTEXTRENDERER_HPP
