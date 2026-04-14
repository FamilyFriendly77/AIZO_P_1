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
  double shellOneTimesSum;
  double shellTwoTimesSum;
  std::vector<double> insertAvgTimes;
  std::vector<double> heapAvgTimes;
  std::vector<double> quickAvgTimes;
  std::vector<double> shellOneAvgTimes;
  std::vector<double> shellTwoAvgTimes;
  if (Config::inTestMode.getValue()) {
    // READING ARRAY FROM FILE AND TESTING ALL ALGS
    int *arr = dataUtil.readArrayFromFile();
    std::string alg = Config::testSortingAlg.getValue();
    std::cout << "Testing " << alg << std::endl;
    if (alg == "quickSort")
      testingUtil.testSortingTime(sorter.quickSort, arr,
                                  dataUtil.getArrayLen());
    else if (alg == "insertSort")
      testingUtil.testSortingTime(sorter.insertSort, arr,
                                  dataUtil.getArrayLen());
    else if (alg == "shellSortOne")
      testingUtil.testSortingTime(sorter.shellSortOne, arr,
                                  dataUtil.getArrayLen());
    else if (alg == "shellSortTwo")
      testingUtil.testSortingTime(sorter.shellSortTwo, arr,
                                  dataUtil.getArrayLen());
    else if (alg == "heapSort")
      testingUtil.testSortingTime(sorter.heapSort, arr, dataUtil.getArrayLen());
  } else {
    int *arr;
    for (int i = 0; i < Config::testCasesArrayLengths.getValue().size(); i++) {
      dataUtil.setArrayLen(Config::testCasesArrayLengths.getValue().at(i));
      quickTimesSum = 0.0;
      insertTimesSum = 0.0;
      heapTimesSum = 0.0;
      shellOneTimesSum = 0.0;
      shellTwoTimesSum = 0.0;
      for (int j = 0; j < Config::testRepetitionCounter.getValue(); j++) {
        arr = dataUtil.generateRandomArray();
        std::cout << "QuickSort" << std::endl;
        quickTimesSum += testingUtil.testSortingTime(sorter.quickSort, arr,
                                                     dataUtil.getArrayLen());
        std::cout << "InsertSort" << std::endl;
        insertTimesSum += testingUtil.testSortingTime(sorter.insertSort, arr,
                                                      dataUtil.getArrayLen());
        std::cout << "ShellSort - Ciura" << std::endl;
        shellOneTimesSum += testingUtil.testSortingTime(
            sorter.shellSortOne, arr, dataUtil.getArrayLen());
        std::cout << "ShellSort - 2^k - 1" << std::endl;
        shellTwoTimesSum += testingUtil.testSortingTime(
            sorter.shellSortTwo, arr, dataUtil.getArrayLen());
        std::cout << "HeapSort" << std::endl;
        heapTimesSum += testingUtil.testSortingTime(sorter.heapSort, arr,
                                                    dataUtil.getArrayLen());
      }
      quickAvgTimes.push_back(quickTimesSum /
                              Config::testRepetitionCounter.getValue());
      insertAvgTimes.push_back(insertTimesSum /
                               Config::testRepetitionCounter.getValue());
      shellOneAvgTimes.push_back(shellOneTimesSum /
                                 Config::testRepetitionCounter.getValue());
      shellTwoAvgTimes.push_back(shellTwoTimesSum /
                                 Config::testRepetitionCounter.getValue());

      heapAvgTimes.push_back(heapTimesSum /
                             Config::testRepetitionCounter.getValue());
    }
  }
  return 0;
};
