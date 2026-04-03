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
      std::memcpy(arrCpy, arr, sizeof(T) * arrLen);
      auto start = std::chrono::high_resolution_clock::now();
      sort(arrCpy, arrLen);
      auto end = std::chrono::high_resolution_clock::now();
      if (Config::printAfterSorting.getValue()) {
        for (int i = 0; i < arrLen; i++) {
          std::cout << arrCpy[i];
        }
      }
      total_time += (end - start);
    }
    double averageSeconds = total_time.count() / repetitionsCounter;
    return averageSeconds;
  };
};
