#include "dataUtility.hpp"
#include "sortingMachine.hpp"
class Main {
public:
  SortingMachine<int> sorter = SortingMachine<int>();
};
int main(int argc, char *argv[]) {
  DataUtility<int> dataUtil = DataUtility<int>();

  if (argc == 2) {
    Config::setConfigFile(argv[1]);
  } else {
    Config::setConfigFile("Config.JSON");
  }

  int *arr = dataUtil.generateRandomArray();
  for (int i = 0; i < 100; i++) {
    std::cout << arr[i] << std::endl;
  }
  return 0;
};
