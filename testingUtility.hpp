#include "config.hpp"
#include "dataUtility.hpp"
#include <chrono>
#include <cstdlib>
#include <iostream>
template <typename T> class TestingUtility {
private:
  int repetitionsCounter = Config::testRepetitionCounter.getValue()
                               ? Config::testRepetitionCounter.getValue()
                               : 100;

public:
  DataUtility<T> dataUtil = DataUtility<T>();
  void setRepetitionsCounter(int counter) { repetitionsCounter = counter; };

  // returns average sorting time for specific array and specific alg
  double testSortingTime(void (*sort)(T *, int)) {
    std::chrono::duration<double> result(0);
    for (int i = 0; i < repetitionsCounter; i++) {
      T *arr;
      if (Config::inTestMode.getValue())
        arr = dataUtil.readArrayFromFile();
      else
        arr = dataUtil.generateRandomArray();
      // benchmark
      auto start = std::chrono::high_resolution_clock::now();
      sort(arr, dataUtil.getArrayLen());
      auto end = std::chrono::high_resolution_clock::now();
      if (Config::printAfterSorting.getValue() ||
          Config::inTestMode.getValue()) {
        std::cout << "SORTED ARRAY:" << std::endl;
        for (int i = 0; i < dataUtil.getArrayLen(); i++) {

          std::cout << arr[i] << std::endl;
        }
      }
      if (Config::testIfSorted.getValue()) {
        if (isSorted(arr, dataUtil.getArrayLen())) {
          std::cout << "Sorting was successful!" << std::endl;
        } else {
          std::cout << "Somethig went wrong while sorting!" << std::endl;
        }
      }
      std::cout << "===============================" << std::endl;

      result += (end - start);

      free(arr);
    }
    // resets seed after running all tests
    dataUtil.setSeed();
    return result.count();
  };
  bool isSorted(T *arr, int arrLen) {
    for (int i = 0; i < arrLen - 1; i++) {
      if (arr[i] > arr[i + 1])
        return false;
    }
    return true;
  }
};
