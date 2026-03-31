#include "config.hpp"
#include <fstream>

using json = nlohmann::json;

Setting<unsigned int> Config::randomSeed =
    Setting<unsigned int>("randomSeed", 123445856);

Setting<bool> Config::inTestMode = Setting<bool>("testMode", false);

Setting<std::string> Config::testFilename =
    Setting<std::string>("testFilename", "tests.txt");

Setting<int> Config::testArrayLen = Setting<int>("testArrayLen", 10);

Setting<std::string> Config::configFile =
    Setting<std::string>("configFilename");
Setting<int> Config::testRepetitionCounter =
    Setting<int>("testRepetitionCounter", 100);
Setting<bool> Config::printAfterSorting =
    Setting<bool>("printAfterSorting", true);
Setting<bool> Config::printAfterGenerating =
    Setting<bool>("printAfterGenerating", true);
Setting<std::string> Config::testSortingAlg =
    Setting<std::string>("testSortingAlg");
void Config::setConfigFile(std::string filename) {
  configFile.setSetting(filename);
}
void Config::loadConfigFromFile() {
  std::ifstream f(Config::configFile.getValue());
  json config = json::parse(f);
  randomSeed.setSetting(config[randomSeed.getLabel()]);
  inTestMode.setSetting(config[inTestMode.getLabel()]);
  testFilename.setSetting(config[testFilename.getLabel()]);
  testArrayLen.setSetting(config[testArrayLen.getLabel()]);
  testRepetitionCounter.setSetting(config[testRepetitionCounter.getLabel()]);
  printAfterSorting.setSetting(config[printAfterSorting.getLabel()]);
  printAfterGenerating.setSetting(config[printAfterGenerating.getLabel()]);
}
