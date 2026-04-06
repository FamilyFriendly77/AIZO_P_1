#ifndef CONFIG_HPP
#define CONFIG_HPP
#include "nlohmann/json.hpp"
#include "setting.hpp"
#include <string>
enum PivotStrategy { FIRST, LAST, MIDDLE, RANDOM };
class Config {
private:
  static Setting<std::string> configFile;

public:
  static Setting<unsigned int> randomSeed;
  static Setting<bool> inTestMode;
  static Setting<std::string> testFilename;
  static Setting<int> testArrayLen;
  static Setting<int> testRepetitionCounter;
  static Setting<std::string> testSortingAlg;
  static Setting<bool> printAfterGenerating;
  static Setting<bool> printAfterSorting;
  static Setting<bool> printBeforeSorting;
  static Setting<PivotStrategy> quickSortPivot;
  static Setting<bool> testIfSorted;
  static void loadConfigFromFile();
  static void setConfigFile(std::string filename);
};
#endif
