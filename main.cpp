#include "config.hpp"
#include "sortingMachine.hpp"
class Main {
private:
  SortingMachine<int> sorter = SortingMachine<int>();

public:
};
int main(int argc, char *argv[]) {
  if (argc == 2) {
    Config::setConfigFile(argv[1]);
  } else {
    Config::setConfigFile("Config.JSON");
  }

  return 0;
};
