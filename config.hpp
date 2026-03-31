#include "nlohmann/json.hpp"
#include "setting.hpp"
#include <string>
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
  static void loadConfigFromFile();
  static void setConfigFile(std::string filename);
};
