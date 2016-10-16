#include <SDL.h>
#include <atomic>
#include <chrono>
#include <thread>
#include "Game.hpp"

Game::Game(const char* title) : window(rendering::createWindow(title)) {
  SDL_InitSubSystem(SDL_INIT_EVENTS);
}

Game::~Game() {
  window->stop();
  SDL_QuitSubSystem(SDL_INIT_EVENTS);
}

void Game::run() {
  auto scene = objects::createScene();
  window->render(scene);

  std::atomic_bool done(false);
  std::thread sleeper([&done] () {
    std::this_thread::sleep_for(std::chrono::seconds(5));
    done.store(true);
  });
  while (!done) {
    SDL_Event event;
    while (SDL_WaitEventTimeout(&event, 5)) {

    }
  }
  sleeper.join();
}
