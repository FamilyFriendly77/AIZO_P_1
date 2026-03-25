#include "config.hpp"

void Config::setConfigFile(std::string filename) {
  configFile.setSetting(filename);
}
