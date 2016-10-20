#ifndef ASTEROIDS_LOGGING_HPP
#define ASTEROIDS_LOGGING_HPP

#include <Poco/Logger.h>

#define log_debug(name, msg, ...) \
    do { \
      static Poco::Logger& logger = Poco::Logger::get(name); \
      logger.debug(msg, ##__VA_ARGS__); \
    } while(0)

#define log_info(name, msg, ...) \
    do { \
      static Poco::Logger& logger = Poco::Logger::get(name); \
      logger.information(msg, ##__VA_ARGS__); \
    } while(0)

#define log_fatal(name, msg, ...) \
    do { \
      static Poco::Logger& logger = Poco::Logger::get(name); \
      logger.fatal(msg, ##__VA_ARGS__); \
    } while(0)

#endif //ASTEROIDS_LOGGING_HPP
