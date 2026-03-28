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
  static void loadConfigFromFile();
  static void setConfigFile(std::string filename);
};
