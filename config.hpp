#include "setting.hpp"
#include <string>
class Config {
private:
  static Setting<std::string> configFile;

public:
  static Setting<int> randomSeed;
  static Setting<bool> inTestMode;
  static Setting<std::string> testFilename;
  static void loadConfigFromFile();
  static void setConfigFile(std::string filename);
};
