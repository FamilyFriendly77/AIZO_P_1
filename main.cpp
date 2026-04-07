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
  DataUtility<int> dataUtil = DataUtility<int>();
  SortingMachine<int> sorter = SortingMachine<int>();
  TestingUtility<int> testingUtil = TestingUtility<int>();
  std::cout << "Random data generator max value: " << RAND_MAX << std::endl;
  for (int i = 0; i < Config::testRepetitionCounter.getValue(); i++) {
    int *arr = dataUtil.generateRandomArray();
    testingUtil.testSortingTime(sorter.quickSort, arr,
                                Config::testArrayLen.getValue());
  }
  return 0;
};
