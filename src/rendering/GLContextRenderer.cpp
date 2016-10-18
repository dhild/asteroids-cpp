#include <Poco/Logger.h>
#include <glbinding/gl/gl.h>
#include <glbinding/Binding.h>
#include <mutex>
#include <thread>
#include "GLContextRenderer.hpp"
#include "PlayerRenderer.hpp"

using namespace rendering;
using namespace objects;

namespace {

  class GLContextHandler {
    const SDL_GLContext glContext;
    PlayerRenderer playerRenderer;
  public:
    explicit GLContextHandler(SDL_Window* window);
    GLContextHandler(const GLContextHandler&) = delete;
    GLContextHandler& operator=(const GLContextHandler&) = delete;
    ~GLContextHandler();

    void drawOnce(std::shared_ptr<const ObjectScene> scene);
  };
}

void rendering::run_render_loop(SDL_Window* window,
                                std::shared_ptr<const ObjectScene> scene,
                                std::shared_ptr<std::atomic_bool> running) {
  GLContextHandler glContext(window);

  while ((*running).load()) {
    glContext.drawOnce(scene);

    SDL_GL_SwapWindow(window);
    std::this_thread::sleep_for(std::chrono::milliseconds(10));
  }
}

static SDL_GLContext initContext(SDL_Window* window) {
  SDL_GLContext glContext = SDL_GL_CreateContext(window);
  if (!glContext) {
    Poco::Logger& logger = Poco::Logger::get("rendering.GLContextRenderer");
    logger.fatal(SDL_GetError());
    throw std::runtime_error(SDL_GetError());
  }
  glbinding::Binding::initialize(false);
  return glContext;
}

GLContextHandler::GLContextHandler(SDL_Window* window) : glContext(initContext(window)), playerRenderer() {
}

static void clearDrawing() {
  static float value = 0.0;
  gl::glClearColor(value, value, value, 1);
  gl::glClear(gl::GL_COLOR_BUFFER_BIT);
  if (value < 1.0) {
    value += 0.001;
  }
}

static void drawAsteroid(const Asteroid&) {

}

static void drawShot(const LaserShot&) {

}

void GLContextHandler::drawOnce(std::shared_ptr<const ObjectScene> scene) {
  clearDrawing();

  playerRenderer.draw(scene->getPlayer());

  std::for_each(scene->beginAsteroids(), scene->endAsteroids(), drawAsteroid);
  std::for_each(scene->beginShots(), scene->endShots(), drawShot);

}

GLContextHandler::~GLContextHandler() {
  if (glContext) {
    SDL_GL_DeleteContext(glContext);
  }
}
