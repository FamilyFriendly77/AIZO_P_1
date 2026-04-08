#include "dataUtility.hpp"
#include "sortingMachine.hpp"
#include "testingUtility.hpp"
#include <cstdlib>
#include <iostream>
class Main {
public:
  SortingMachine<int> sorter = SortingMachine<int>();
};
int main(int argc, char *argv[]) {
  if (argc == 2) {
    Config::setConfigFile(argv[1]);
  } else {
    Config::setConfigFile("config.JSON");
  }
  Config::loadConfigFromFile();
  SortingMachine<int> sorter = SortingMachine<int>();
  TestingUtility<int> testingUtil = TestingUtility<int>();
  testingUtil.testSortingTime(sorter.insertSort);
  std::cout << "Random data generator max value: " << RAND_MAX << std::endl;
  for (int i = 0; i < 2; i++) {
    testingUtil.testSortingTime(sorter.quickSort);
  }

  return 0;
};
