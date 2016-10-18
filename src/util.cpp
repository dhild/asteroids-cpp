#include <fstream>
#include "util.hpp"

const char* base_directory = ASTEROIDS_BASE_DIR;

#ifdef __linux__
const char* separator = "/";
#elif _WIN32
const char* separator = "\\";
#else
#error Unknown file separator!
#endif

std::string util::loadFile(const char* resourceName) {
  std::string filename(base_directory);
  filename += separator;
  filename += "data";
  filename += separator;
  filename += resourceName;

  std::ifstream file(filename);
  std::string contents((std::istreambuf_iterator<char>(file)),
                       std::istreambuf_iterator<char>());
  return contents;
}
