#include <Poco/Logger.h>
#include <glbinding/gl/gl.h>
#include <glbinding/Binding.h>
#include <mutex>
#include <thread>
#include "GLContextRenderer.hpp"

using namespace rendering;
using namespace objects;

namespace {
  class GLContextHandler {
    const SDL_GLContext glContext;
  public:
    explicit GLContextHandler(SDL_Window* window) : glContext(SDL_GL_CreateContext(window)) {
      if (!glContext) {
        Poco::Logger& logger = Poco::Logger::get("rendering.GLContextRenderer");
        logger.fatal(SDL_GetError());
        std::exit(1);
      }
      glbinding::Binding::initialize(false);
    }
    GLContextHandler(const GLContextHandler&) = delete;
    GLContextHandler& operator=(const GLContextHandler&) = delete;

    ~GLContextHandler() {
      if (glContext) {
        SDL_GL_DeleteContext(glContext);
      }
    }
  };
}

static void clearDrawing() {
  static float value = 0.0;
  gl::glClearColor(value, value, value, 1);
  gl::glClear(gl::GL_COLOR_BUFFER_BIT);
  if (value < 1.0) {
    value += 0.001;
  }
}

static void drawPlayer(const Player&) {

}

static void drawAsteroid(const Asteroid&) {

}

static void drawShot(const LaserShot&) {

}

void rendering::run_render_loop(SDL_Window* window,
                                std::shared_ptr<const ObjectScene> scene,
                                std::shared_ptr<std::atomic_bool> running) {
  GLContextHandler glContext(window);
  while ((*running).load()) {
    clearDrawing();

    drawPlayer(scene->getPlayer());

    std::for_each(scene->beginAsteroids(), scene->endAsteroids(), drawAsteroid);
    std::for_each(scene->beginShots(), scene->endShots(), drawShot);

    SDL_GL_SwapWindow(window);
    std::this_thread::sleep_for(std::chrono::milliseconds(10));
  }
}


