#include <glbinding/gl/gl.h>
#include <glbinding/Binding.h>
#include <mutex>
#include <thread>
#include "../logging.hpp"
#include "GLContextRenderer.hpp"
#include "PlayerRenderer.hpp"
#include "AsteroidRenderer.hpp"
#include "LaserShotRenderer.hpp"

using namespace rendering;
using namespace objects;

namespace {

  class GLContextHandler {
    const SDL_GLContext glContext;
    PlayerRenderer playerRenderer;
    AsteroidRenderer asteroidRenderer;
    LaserShotRenderer laserShotRenderer;
  public:
    explicit GLContextHandler(SDL_Window* window);
    GLContextHandler(const GLContextHandler&) = delete;
    GLContextHandler& operator=(const GLContextHandler&) = delete;
    ~GLContextHandler();

    void drawOnce(std::shared_ptr<const ObjectScene> scene);
  };
}

static void handleResizes(SDL_Window* window, int& runningWidth, int& runningHeight) {
  int width, height;
  SDL_GL_GetDrawableSize(window, &width, &height);

  if (width == runningWidth && height == runningHeight) {
    return;
  }
  runningWidth = width;
  runningHeight = height;

  gl::glViewport(0, 0, width, height);
}

void rendering::run_render_loop(SDL_Window* window,
                                std::shared_ptr<const ObjectScene> scene,
                                std::shared_ptr<std::atomic_bool> running) {
  GLContextHandler glContext(window);

  int width, height;
  while ((*running).load()) {
    handleResizes(window, width, height);

    glContext.drawOnce(scene);

    SDL_GL_SwapWindow(window);
    std::this_thread::sleep_for(std::chrono::milliseconds(10));
  }
}

static SDL_GLContext initContext(SDL_Window* window) {
  SDL_GLContext glContext = SDL_GL_CreateContext(window);
  if (!glContext) {
    log_fatal("rendering.GLContextRenderer", SDL_GetError());
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
  if (value < 0.15) {
    value += 0.001;
  }
}

void GLContextHandler::drawOnce(std::shared_ptr<const ObjectScene> scene) {
  clearDrawing();

  playerRenderer.draw(scene->getPlayer());

  scene->each_asteroid(std::bind(&AsteroidRenderer::draw, &asteroidRenderer, std::placeholders::_1));

  scene->each_shot(std::bind(&LaserShotRenderer::draw, &laserShotRenderer, std::placeholders::_1));

}

GLContextHandler::~GLContextHandler() {
  if (glContext) {
    SDL_GL_DeleteContext(glContext);
  }
}
