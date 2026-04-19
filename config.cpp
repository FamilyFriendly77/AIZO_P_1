#include "config.hpp"
#include <exception>
#include <fstream>
#include <iostream>
using json = nlohmann::json;

Setting<int> Config::randomSeed = Setting<int>("randomSeed");

Setting<bool> Config::inTestMode = Setting<bool>("testMode");

Setting<std::string> Config::testFilename =
    Setting<std::string>("testFilename", "tests.txt");

Setting<std::vector<int>> Config::testCasesArrayLengths =
    Setting<std::vector<int>>("testCasesArrayLengths");

Setting<std::string> Config::configFile =
    Setting<std::string>("configFilename");
Setting<int> Config::testRepetitionCounter =
    Setting<int>("testRepetitionCounter");
Setting<bool> Config::printAfterSorting = Setting<bool>("printAfterSorting");

Setting<bool> Config::printAfterGenerating =
    Setting<bool>("printAfterGenerating");
Setting<std::string> Config::testSortingAlg =
    Setting<std::string>("testSortingAlg");
Setting<bool> Config::testIfSorted = Setting<bool>("testIfSorted");
void Config::setConfigFile(std::string filename) {
  configFile.setSetting(filename);
}
Setting<PivotStrategy> Config::quickSortPivot =
    Setting<PivotStrategy>("quickSortPivot");
Setting<bool> Config::testINT = Setting<bool>("testINT");
Setting<bool> Config::testFLOAT = Setting<bool>("testFLOAT");
Setting<bool> Config::testDOUBLE = Setting<bool>("testDOUBLE");
Setting<bool> Config::testCHAR = Setting<bool>("testCHAR");

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
  randomSeed.setSetting(config.value(randomSeed.getLabel(), 123456));
  inTestMode.setSetting(config.value(inTestMode.getLabel(), true));
  testSortingAlg.setSetting(
      config.value(testSortingAlg.getLabel(), "heapSort"));
  testFilename.setSetting(config.value(testFilename.getLabel(), "test.txt"));
  testCasesArrayLengths.setSetting(
      config.value(testCasesArrayLengths.getLabel(), std::vector<int>{}));
  testRepetitionCounter.setSetting(
      config.value(testRepetitionCounter.getLabel(), 100));
  printAfterSorting.setSetting(
      config.value(printAfterSorting.getLabel(), true));
  printAfterGenerating.setSetting(
      config.value(printAfterGenerating.getLabel(), true));
  testIfSorted.setSetting(config.value(testIfSorted.getLabel(), true));
  testINT.setSetting(config.value(testINT.getLabel(), false));
  testFLOAT.setSetting(config.value(testFLOAT.getLabel(), false));
  testDOUBLE.setSetting(config.value(testDOUBLE.getLabel(), false));
  testCHAR.setSetting(config.value(testCHAR.getLabel(), false));
  std::string pivot = config.value(quickSortPivot.getLabel(), "FIRST");
  if (pivot == "FIRST") {
    quickSortPivot.setSetting(FIRST);
  } else if (pivot == "LAST") {
    quickSortPivot.setSetting(LAST);
  } else if (pivot == "MIDDLE") {
    quickSortPivot.setSetting(MIDDLE);
  } else if (pivot == "RANDOM") {
    quickSortPivot.setSetting(RANDOM);
  }
  std::cout << "Succesfully loaded config from "
            << Config::configFile.getValue() << std::endl;
}
