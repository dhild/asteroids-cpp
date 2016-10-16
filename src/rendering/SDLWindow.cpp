#include <SDL.h>
#include <Poco/Thread.h>
#include <Poco/Logger.h>
#include <thread>
#include "../rendering.hpp"
#include "GLContextRenderer.hpp"

using namespace rendering;

namespace {
  class SDLWindow : public Window {
    SDL_Window* window;
    std::thread renderingThread;
    std::shared_ptr<std::atomic_bool> renderFlag;

  public:
    SDLWindow(const char* title, int width, int height)
        : window(nullptr), renderFlag(std::make_shared<std::atomic_bool>(true)) {
      Poco::Logger& logger = Poco::Logger::get("rendering.SDLWindow");
      if (SDL_InitSubSystem(SDL_INIT_VIDEO) != 0) {
        logger.fatal(SDL_GetError());
        std::exit(1);
      }
      window = SDL_CreateWindow(title,
                                SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                                width, height,
                                SDL_WINDOW_RESIZABLE | SDL_WINDOW_OPENGL);
      if (!window) {
        logger.fatal(SDL_GetError());
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

    virtual void render(std::shared_ptr<const objects::ObjectScene> scene) override {
      renderFlag->store(true);
      renderingThread = std::thread(rendering::run_render_loop, window, scene, renderFlag);
    }

    virtual void stop() override {
      renderFlag->store(false);
      if (renderingThread.joinable()) {
        renderingThread.join();
      }
    }
  };
}

std::shared_ptr<Window> rendering::createWindow(const char* name, int width, int height) {
  return std::make_shared<SDLWindow>(name, width, height);
}
