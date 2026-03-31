#include "config.hpp"

using json = nlohmann::json;

Setting<unsigned int> Config::randomSeed =
    Setting<unsigned int>("randomSeed", 12344585654634345);

Setting<bool> Config::inTestMode = Setting<bool>("TestMode", false);

Setting<std::string> Config::testFilename =
    Setting<std::string>("testFileName", "tests.txt");

Setting<int> Config::testArrayLen = Setting<int>("testArrayLen", 10);

Setting<std::string> Config::configFile =
    Setting<std::string>("configFilename");
Setting<int> Config::testRepetitionCounter =
    Setting<int>("testRepetitionCounter", 100);
Setting<bool> Config::printAfterSorting =
    Setting<bool>("printAfterSorting", true);
Setting<bool> Config::printAfterGenerating =
    Setting<bool>("printAfterGenerating", true);
Setting<std::string> Config::sortingAlg = Setting<std::string>("sortingAlg");
void Config::setConfigFile(std::string filename) {
  configFile.setSetting(filename);
}
