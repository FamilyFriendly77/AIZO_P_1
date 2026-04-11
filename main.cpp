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
  DataUtility<int> dataUtil = DataUtility<int>();
  double insertTimesSum;
  double heapTimesSum;
  double quickTimesSum;
  double shellTimesSum;
  std::vector<double> insertAvgTimes;
  std::vector<double> heapAvgTimes;
  std::vector<double> quickAvgTimes;
  std::vector<double> shellAvgTimes;
  if (Config::inTestMode.getValue()) {
    // READING ARRAY FROM FILE AND TESTING ALL ALGS
  } else {
    int *arr;
    for (int i = 0; i < Config::testCasesArrayLengths.getValue().size(); i++) {
      dataUtil.setArrayLen(Config::testCasesArrayLengths.getValue().at(i));
      quickTimesSum = 0.0;
      insertTimesSum = 0.0;
      heapTimesSum = 0.0;
      shellTimesSum = 0.0;
      for (int j = 0; j < Config::testRepetitionCounter.getValue(); j++) {
        arr = dataUtil.generateRandomArray();
        quickTimesSum += testingUtil.testSortingTime(sorter.quickSort, arr,
                                                     dataUtil.getArrayLen());
        insertTimesSum += testingUtil.testSortingTime(sorter.insertSort, arr,
                                                      dataUtil.getArrayLen());
      }
      quickAvgTimes.push_back(quickTimesSum /
                              Config::testRepetitionCounter.getValue());
      insertAvgTimes.push_back(insertTimesSum /
                               Config::testRepetitionCounter.getValue());
    }
  }

  std::cout << "Random data generator max value: " << RAND_MAX << std::endl;

  return 0;
};
