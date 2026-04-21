#include "dataUtility.hpp"
#include "sortingMachine.hpp"
#include "testingUtility.hpp"
#include <algorithm>
#include <cstdlib>
#include <iostream>

enum GenerateStrategy {
  RANDOM_ARRAY,
  SORTED_33,
  SORTED_66,
  SORTED_ASC,
  SORTED_DSC
};

template <typename T>
void runTests(GenerateStrategy strat, std::string name,
              TestingUtility<T> testingUtil, SortingMachine<T> sorter,
              DataUtility<T> dataUtil) {
  T *arr;
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

  std::cout << name << std::endl;
  std::cout << "------------------------" << std::endl;

  for (int i = 0; i < Config::testCasesArrayLengths.getValue().size(); i++) {
    dataUtil.setArrayLen(Config::testCasesArrayLengths.getValue().at(i));
    std::cout << "Currently testing Arrays with the length of "
              << dataUtil.getArrayLen() << " items." << std::endl;
    std::cout << "------------------------" << std::endl;
    quickTimesSum = 0.0;
    insertTimesSum = 0.0;
    heapTimesSum = 0.0;
    shellOneTimesSum = 0.0;
    shellTwoTimesSum = 0.0;
    for (int j = 0; j < Config::testRepetitionCounter.getValue(); j++) {
      switch (strat) {
      case RANDOM_ARRAY:
        arr = dataUtil.generateRandomArray();
        break;
      case SORTED_33:
        arr = dataUtil.generatePartialySortedArray(0.33);
        break;
      case SORTED_66:
        arr = dataUtil.generatePartialySortedArray(0.66);
        break;
      case SORTED_ASC:
        arr = dataUtil.generateAscSortedArray();
        break;
      case SORTED_DSC:
        arr = dataUtil.generateDscSortedArray();
        break;
      }
      if (Config::testIfSorted.getValue())
        std::cout << "QuickSort" << std::endl;
      quickTimesSum += testingUtil.testSortingTime(sorter.quickSort, arr,
                                                   dataUtil.getArrayLen());
      if (Config::testIfSorted.getValue())
        std::cout << "InsertSort" << std::endl;
      insertTimesSum += testingUtil.testSortingTime(sorter.insertSort, arr,
                                                    dataUtil.getArrayLen());
      if (Config::testIfSorted.getValue())
        std::cout << "ShellSort - Ciura" << std::endl;
      shellOneTimesSum += testingUtil.testSortingTime(sorter.shellSortOne, arr,
                                                      dataUtil.getArrayLen());
      if (Config::testIfSorted.getValue())
        std::cout << "ShellSort - 2^k - 1" << std::endl;
      shellTwoTimesSum += testingUtil.testSortingTime(sorter.shellSortTwo, arr,
                                                      dataUtil.getArrayLen());
      if (Config::testIfSorted.getValue())
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
  std::cout << "Average sorting times for QuickSort" << std::endl;
  for (int i = 0; i < Config::testCasesArrayLengths.getValue().size(); i++) {
    std::cout << quickAvgTimes[i] << std::endl;
  }
  std::cout << "Average sorting times for InsertSort" << std::endl;
  for (int i = 0; i < Config::testCasesArrayLengths.getValue().size(); i++) {
    std::cout << insertAvgTimes[i] << std::endl;
  }
  std::cout << "Average sorting times for ShellSort - Ciura" << std::endl;
  for (int i = 0; i < Config::testCasesArrayLengths.getValue().size(); i++) {
    std::cout << shellOneAvgTimes[i] << std::endl;
  }
  std::cout << "Average sorting times for ShellSort - 2^k - 1" << std::endl;
  for (int i = 0; i < Config::testCasesArrayLengths.getValue().size(); i++) {
    std::cout << shellTwoAvgTimes[i] << std::endl;
  }
  std::cout << "Average sorting times for heapSort" << std::endl;
  for (int i = 0; i < Config::testCasesArrayLengths.getValue().size(); i++) {
    std::cout << heapAvgTimes[i] << std::endl;
  }
}

int main(int argc, char *argv[]) {
  std::cout << "ver: ";
  std::cout << __cplusplus << std::endl;
  if (argc == 2) {
    Config::setConfigFile(argv[1]);
  } else {
    Config::setConfigFile("config.JSON");
  }
  Config::loadConfigFromFile();
  if (Config::inTestMode.getValue()) {
    SortingMachine<double> sorter = SortingMachine<double>();
    TestingUtility<double> testingUtil = TestingUtility<double>();
    DataUtility<double> dataUtil = DataUtility<double>();

    // READING ARRAY FROM FILE AND TESTING ALL ALGS
    double *arr = dataUtil.readArrayFromFile();
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
    if (Config::testINT.getValue()) {
      std::cout << "TESTING ON INT DATATYPE:" << std::endl;
      DataUtility<int> dataUtil = DataUtility<int>();
      TestingUtility<int> testingUtil = TestingUtility<int>();
      SortingMachine<int> sorter = SortingMachine<int>();

      runTests<int>(RANDOM_ARRAY, "Randomly generated array", testingUtil,
                    sorter, dataUtil);
      runTests<int>(SORTED_33, "Partially sorted array - 33%", testingUtil,
                    sorter, dataUtil);
      runTests<int>(SORTED_66, "Partially sorted array - 66%", testingUtil,
                    sorter, dataUtil);
      runTests<int>(SORTED_ASC, "ASC sorted array", testingUtil, sorter,
                    dataUtil);
      runTests<int>(SORTED_DSC, "DSC sorted array", testingUtil, sorter,
                    dataUtil);
    }

    if (Config::testDOUBLE.getValue()) {
      std::cout << "TESTING ON DOUBLE DATATYPE:" << std::endl;

      DataUtility<double> dataUtil = DataUtility<double>();
      TestingUtility<double> testingUtil = TestingUtility<double>();
      SortingMachine<double> sorter = SortingMachine<double>();

      runTests<double>(RANDOM_ARRAY, "Randomly generated array", testingUtil,
                       sorter, dataUtil);
      runTests<double>(SORTED_33, "Partially sorted array - 33%", testingUtil,
                       sorter, dataUtil);
      runTests<double>(SORTED_66, "Partially sorted array - 66%", testingUtil,
                       sorter, dataUtil);
      runTests<double>(SORTED_ASC, "ASC sorted array", testingUtil, sorter,
                       dataUtil);
      runTests<double>(SORTED_DSC, "DSC sorted array", testingUtil, sorter,
                       dataUtil);
    }
    if (Config::testFLOAT.getValue()) {
      std::cout << "TESTING ON FLOAT DATATYPE:" << std::endl;

      DataUtility<float> dataUtil = DataUtility<float>();
      TestingUtility<float> testingUtil = TestingUtility<float>();
      SortingMachine<float> sorter = SortingMachine<float>();

      runTests<float>(RANDOM_ARRAY, "Randomly generated array", testingUtil,
                      sorter, dataUtil);
      runTests<float>(SORTED_33, "Partially sorted array - 33%", testingUtil,
                      sorter, dataUtil);
      runTests<float>(SORTED_66, "Partially sorted array - 66%", testingUtil,
                      sorter, dataUtil);
      runTests<float>(SORTED_ASC, "ASC sorted array", testingUtil, sorter,
                      dataUtil);
      runTests<float>(SORTED_DSC, "DSC sorted array", testingUtil, sorter,
                      dataUtil);
    }

    if (Config::testCHAR.getValue()) {
      std::cout << "TESTING ON CHAR DATATYPE:" << std::endl;

      DataUtility<char> dataUtil = DataUtility<char>();
      TestingUtility<char> testingUtil = TestingUtility<char>();
      SortingMachine<char> sorter = SortingMachine<char>();

      runTests<char>(RANDOM_ARRAY, "Randomly generated array", testingUtil,
                     sorter, dataUtil);
      runTests<char>(SORTED_33, "Partially sorted array - 33%", testingUtil,
                     sorter, dataUtil);
      runTests<char>(SORTED_66, "Partially sorted array - 66%", testingUtil,
                     sorter, dataUtil);
      runTests<char>(SORTED_ASC, "ASC sorted array", testingUtil, sorter,
                     dataUtil);
      runTests<char>(SORTED_DSC, "DSC sorted array", testingUtil, sorter,
                     dataUtil);
    }
  }
  return 0;
};
