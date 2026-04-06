#include "config.hpp"
#include <chrono>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <stdexcept>
template <typename T> class TestingUtility {
private:
  int repetitionsCounter = Config::testRepetitionCounter.getValue()
                               ? Config::testRepetitionCounter.getValue()
                               : 100;

public:
  void setRepetitionsCounter(int counter) { repetitionsCounter = counter; };
  template <typename Func>
  // returns average sorting time for specific array and specific alg
  double testSortingTime(Func sort, T *arr, int arrLen) {
    std::chrono::duration<double> total_time(0);
    // this handels most cases of when something goes wrong, if memory is not
    // avaliable we can't run tests so we throw an exeption
    T *arrCpy = (T *)malloc(sizeof(T) * arrLen);
    if (arrCpy == NULL) {
      throw std::runtime_error(
          "Can't run due to memory error - can't alocate enough memory");
    }

    for (int i = 0; i < repetitionsCounter; i++) {
      // creating copy of an array to be sorted for every repetition of
      // benchmark
      std::memcpy(arrCpy, arr, sizeof(T) * arrLen);
      std::cout << "===============================" << std::endl;
      if (Config::printBeforeSorting.getValue()) {
        std::cout << "COPIED ARRAY:" << std::endl;
        for (int i = 0; i < arrLen; i++) {

          std::cout << arrCpy[i] << std::endl;
        }
      }
      // benchmark
      auto start = std::chrono::high_resolution_clock::now();
      sort(arrCpy, arrLen);
      auto end = std::chrono::high_resolution_clock::now();
      if (Config::printAfterSorting.getValue()) {
        std::cout << "SORTED ARRAY:" << std::endl;
        for (int i = 0; i < arrLen; i++) {

          std::cout << arrCpy[i] << std::endl;
        }
      }
      if (Config::testIfSorted.getValue()) {
        if (isSorted(arrCpy, arrLen)) {
          std::cout << "Sorting was successful!" << std::endl;
        } else {
          std::cout << "Somethig went wrong while sorting!" << std::endl;
        }
      }
      std::cout << "===============================" << std::endl;

      total_time += (end - start);
    }
    free(arrCpy);
    double averageSeconds = total_time.count() / repetitionsCounter;
    return averageSeconds;
  };
  bool isSorted(T *arr, int arrLen) {
    for (int i = 0; i < arrLen - 1; i++) {
      if (arr[i] > arr[i + 1])
        return false;
    }
    return true;
  }
};
