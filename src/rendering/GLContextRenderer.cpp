#include <glbinding/gl/gl.h>
#include <glbinding/Binding.h>
#include <mutex>
#include <thread>
#include "../logging.hpp"
#include "GLContextRenderer.hpp"
#include "../asteroid/AsteroidRenderer.hpp"
#include "../player/PlayerRenderer.hpp"
#include "../shot/LaserShotRenderer.hpp"

using namespace asteroids;
using namespace asteroids::rendering;
using asteroids::asteroid::AsteroidRenderer;
using asteroids::player::PlayerRenderer;
using asteroids::shot::LaserShotRenderer;

namespace {

  SDL_GLContext initContext(SDL_Window* window) {
    SDL_GLContext glContext = SDL_GL_CreateContext(window);
    if (!glContext) {
      log_fatal("rendering.GLContextRenderer", SDL_GetError());
      throw std::runtime_error(SDL_GetError());
    }
    SDL_GL_SetSwapInterval(0);
    glbinding::Binding::initialize(false);
    return glContext;
  }

  void clearDrawing() {
    static float value = 0.0;
    gl::glClearColor(value, value, value, 1);
    gl::glClear(gl::GL_COLOR_BUFFER_BIT);
    if (value < 0.15) {
      value += 0.001;
    }
  }

  class GLContextHandler : public WindowRenderer {
    const SDL_GLContext glContext;
    PlayerRenderer playerRenderer;
    AsteroidRenderer asteroidRenderer;
    LaserShotRenderer shotRenderer;
  public:
    explicit GLContextHandler(SDL_Window* window) : glContext(initContext(window)) {}

    GLContextHandler(const GLContextHandler&) = delete;
    GLContextHandler& operator=(const GLContextHandler&) = delete;

    virtual ~GLContextHandler() {
      if (glContext) {
        SDL_GL_DeleteContext(glContext);
      }
    }

    virtual void resized(int width, int height) const override {
      gl::glViewport(0, 0, width, height);
    }

    virtual void draw(const ObjectScene& scene) const override {
      clearDrawing();

      playerRenderer.render(scene.player());

      scene.each_asteroid(std::bind(&AsteroidRenderer::render, &asteroidRenderer, std::placeholders::_1));

      scene.each_shot(std::bind(&LaserShotRenderer::render, &shotRenderer, std::placeholders::_1));
    }
  };
}

std::unique_ptr<WindowRenderer> asteroids::rendering::create_renderer(SDL_Window* window) {
  return std::make_unique<GLContextHandler>(window);
}
