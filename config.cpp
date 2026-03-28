#include "config.hpp"
Setting<unsigned int> Config::randomSeed = Setting<unsigned int>("randomSeed");
Setting<bool> Config::inTestMode = Setting<bool>("TestMode", false);
Setting<std::string> Config::testFilename =
    Setting<std::string>("testFileName");
Setting<int> Config::testArrayLen = Setting<int>("testArrayLen");
Setting<std::string> Config::configFile =
    Setting<std::string>("configFilename");
void Config::setConfigFile(std::string filename) {
  configFile.setSetting(filename);
}
