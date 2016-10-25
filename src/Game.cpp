#include <SDL.h>
#include <atomic>
#include <chrono>
#include <iostream>
#include <thread>
#include "logging.hpp"
#include "Game.hpp"
#include "objects/GameTicker.hpp"

Game::Game(const char* title) : window(rendering::createWindow(title, 1000, 800)) {
  SDL_InitSubSystem(SDL_INIT_EVENTS);
}

Game::~Game() {
  SDL_QuitSubSystem(SDL_INIT_EVENTS);
}

void Game::run() {
  auto scene = objects::create_scene();
  auto ticker = objects::createTicker(scene);
  window->render(scene);
  ticker->start();

  while (!ticker->isOver()) {
    SDL_Event event;
    while (SDL_WaitEventTimeout(&event, 5)) {
      if (event.type == SDL_WINDOWEVENT) {
        if (event.window.event == SDL_WINDOWEVENT_CLOSE) {
          ticker->signalClosed();
        }
        if (event.window.event == SDL_WINDOWEVENT_SIZE_CHANGED) {
          log_info("Game", "Window resized to %d,%d", event.window.data1, event.window.data2);
        }
      }
    }
  }
  window->stop();
}
