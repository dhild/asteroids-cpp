#include <SDL.h>
#include <atomic>
#include <chrono>
#include <iostream>
#include <thread>
#include <Poco/Logger.h>
#include "Game.hpp"
#include "objects/GameTicker.hpp"

Game::Game(const char* title) : window(rendering::createWindow(title, 1000, 800)) {
  SDL_InitSubSystem(SDL_INIT_EVENTS);
}

Game::~Game() {
  window->stop();
  SDL_QuitSubSystem(SDL_INIT_EVENTS);
}

void Game::run() {
  Poco::Logger& logger = Poco::Logger::get("Game");
  auto scene = objects::createScene();
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
          logger.information("Window resized to %d,%d", event.window.data1, event.window.data2);
        }
      }
    }
  }
}
