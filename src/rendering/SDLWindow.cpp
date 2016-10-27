#include <SDL.h>
#include <Poco/Thread.h>
#include <thread>
#include "../logging.hpp"
#include "../rendering.hpp"
#include "GLContextRenderer.hpp"

using namespace asteroids;
using namespace asteroids::rendering;

namespace {
  class SDLWindow : public Window {
    SDL_Window* window;
    std::thread renderingThread;
    std::shared_ptr<std::atomic_bool> renderFlag;

  public:
    SDLWindow(const char* title, int width, int height)
            : window(nullptr), renderFlag(std::make_shared<std::atomic_bool>(true)) {
      if (SDL_InitSubSystem(SDL_INIT_VIDEO) != 0) {
        log_fatal("rendering.SDLWindow", SDL_GetError());
        std::exit(1);
      }
      SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
      SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
      SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, 0);
      SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
      window = SDL_CreateWindow(title,
                                SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                                width, height,
                                SDL_WINDOW_RESIZABLE | SDL_WINDOW_OPENGL);
      if (!window) {
        log_fatal("rendering.SDLWindow", SDL_GetError());
        std::exit(1);
      }
    }

    virtual ~SDLWindow() {
      stop();
      if (window) {
        SDL_DestroyWindow(window);
      }
      SDL_QuitSubSystem(SDL_INIT_VIDEO);
    }

    virtual void render(std::shared_ptr<const ObjectScene> scene) override;

    virtual void stop() override {
      renderFlag->store(false);
      if (renderingThread.joinable()) {
        renderingThread.join();
      }
    }
  };

  void run_render_loop(SDL_Window* window,
                       std::shared_ptr<const ObjectScene> scene,
                       std::shared_ptr<std::atomic_bool> running) {
    auto glContext = create_renderer(window);

    int lastWidth = 0, lastHeight = 0;
    while ((*running).load()) {
      int width, height;
      SDL_GL_GetDrawableSize(window, &width, &height);

      if (width != lastWidth || height != lastHeight) {
        lastWidth = width;
        lastHeight = height;

        glContext->resized(width, height);
      }

      glContext->draw(*scene);

      SDL_GL_SwapWindow(window);
    }
  }

  void SDLWindow::render(std::shared_ptr<const ObjectScene> scene) {
    renderFlag->store(true);
    renderingThread = std::thread(run_render_loop, window, scene, renderFlag);
  }
}

std::shared_ptr<Window> asteroids::create_window(const char* name, int width, int height) {
  return std::make_shared<SDLWindow>(name, width, height);
}
