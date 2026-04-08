#include "config.hpp"
#include <exception>
#include <fstream>
#include <iostream>
using json = nlohmann::json;

Setting<unsigned int> Config::randomSeed =
    Setting<unsigned int>("randomSeed", 123445856);

Setting<bool> Config::inTestMode = Setting<bool>("testMode", false);

Setting<std::string> Config::testFilename =
    Setting<std::string>("testFilename", "tests.txt");

Setting<int> Config::generatedArrayLen =
    Setting<int>("generatedArrayLen", 10000);

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
Setting<bool> Config::testIfSorted = Setting<bool>("testIfSorted", false);
void Config::setConfigFile(std::string filename) {
  configFile.setSetting(filename);
}
Setting<PivotStrategy> Config::quickSortPivot =
    Setting<PivotStrategy>("quickSortPivot");
void Config::loadConfigFromFile() {
  std::ifstream f(Config::configFile.getValue());
  // checking if file opens, if not, throw an error because it can't be read
  if (!f.is_open()) {
    throw std::runtime_error(
        "Specified config file does not exits or can't be opened");
  }
  json config;
  try {
    config = json::parse(f);
  } catch (std::exception e) {
    std::cerr << "Something went wrong while parsing config!!!";
    return;
  }
  randomSeed.setSetting(config.value(randomSeed.getLabel(), NULL));
  inTestMode.setSetting(config.value(inTestMode.getLabel(), NULL));
  testFilename.setSetting(config.value(testFilename.getLabel(), ""));
  generatedArrayLen.setSetting(
      config.value(generatedArrayLen.getLabel(), NULL));
  testRepetitionCounter.setSetting(
      config.value(testRepetitionCounter.getLabel(), NULL));
  printAfterSorting.setSetting(
      config.value(printAfterSorting.getLabel(), NULL));
  printAfterGenerating.setSetting(
      config.value(printAfterGenerating.getLabel(), NULL));
  testIfSorted.setSetting(config.value(testIfSorted.getLabel(), NULL));
  if (config.value(quickSortPivot.getLabel(), "FIRST") == "FIRST") {
    quickSortPivot.setSetting(FIRST);
  } else if (config.value(quickSortPivot.getLabel(), "") == "LAST") {
    quickSortPivot.setSetting(LAST);
  } else if (config.value(quickSortPivot.getLabel(), "") == "MIDDLE") {
    quickSortPivot.setSetting(MIDDLE);
  } else if (config.value(quickSortPivot.getLabel(), "") == "RANDOM") {
    quickSortPivot.setSetting(RANDOM);
  }
  std::cout << "Succesfully loaded config from "
            << Config::configFile.getValue() << std::endl;
}
