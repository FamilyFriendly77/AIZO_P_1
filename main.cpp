#include "dataUtility.hpp"
#include "sortingMachine.hpp"
#include "testingUtility.hpp"
class Main {
public:
  SortingMachine<int> sorter = SortingMachine<int>();
};
int main(int argc, char *argv[]) {
  DataUtility<int> dataUtil = DataUtility<int>();
  SortingMachine<int> sorter = SortingMachine<int>();
  TestingUtility<int> testingUtil = TestingUtility<int>();
  if (argc == 2) {
    Config::setConfigFile(argv[1]);
  } else {
    Config::setConfigFile("Config.JSON");
  }

  int *arr = dataUtil.readArrayFromFile();
  testingUtil.testSortingTime(sorter.insertSort, arr,
                              Config::testArrayLen.getValue());
  return 0;
};
