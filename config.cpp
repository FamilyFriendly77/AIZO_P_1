#include "config.hpp"
Setting<unsigned int> Config::randomSeed =
    Setting<unsigned int>("randomSeed", 12344585654634345);

Setting<bool> Config::inTestMode = Setting<bool>("TestMode", false);

Setting<std::string> Config::testFilename =
    Setting<std::string>("testFileName");

Setting<int> Config::testArrayLen = Setting<int>("testArrayLen", 100);

Setting<std::string> Config::configFile =
    Setting<std::string>("configFilename");

void Config::setConfigFile(std::string filename) {
  configFile.setSetting(filename);
}
