#include <Poco/ConsoleChannel.h>
#include <Poco/AutoPtr.h>
#include <Poco/Logger.h>
#include "src/Game.hpp"

using Poco::AutoPtr;
using Poco::ConsoleChannel;
using Poco::Logger;

void initLogging() {
  static AutoPtr<ConsoleChannel> channel(new ConsoleChannel);
  Logger::root().setChannel(channel);
}

int main() {
  initLogging();
  asteroids::Game game("Asteroids!");
  game.run();
  return 0;
}
