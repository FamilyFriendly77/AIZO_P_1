#include "config.hpp"
#include "dataUtility.hpp"
#include <chrono>
#include <cstdlib>
#include <exception>
#include <iostream>
#include <system_error>
template <typename T> class TestingUtility {
private:
public:
  // returns average sorting time for specific array and specific alg
  double testSortingTime(void (*sort)(T *, int), T *array, int arrayLen) {
    std::chrono::duration<double> result(0);
    T *arr;
    try {
      memccpy(arr, array, arrayLen);
    } catch (std::exception e) {
      std::cerr << e.what() << std::endl;
    }
    // benchmark
    auto start = std::chrono::high_resolution_clock::now();
    sort(arr, arrayLen);
    auto end = std::chrono::high_resolution_clock::now();
    if (Config::printAfterSorting.getValue() || Config::inTestMode.getValue()) {
      std::cout << "SORTED ARRAY:" << std::endl;
      for (int i = 0; i < arrayLen; i++) {

        std::cout << arr[i] << std::endl;
      }
    }
    if (Config::testIfSorted.getValue()) {
      if (isSorted(arr, arrayLen)) {
        std::cout << "Sorting was successful!" << std::endl;
      } else {
        std::cout << "Somethig went wrong while sorting!" << std::endl;
      }
    }
    std::cout << "===============================" << std::endl;

    result += (end - start);

    free(arr);
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
