#include "config.hpp"
#include "sortingMachine.hpp"
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <string>
#ifndef DATAUTILITY_HPP
#define DATAUTILITY_HPP
template <typename T> class DataUtility {
private:
  int arrayLen;

public:
  DataUtility<T>(int seed = Config::randomSeed.getValue()) { srand(seed); };
  void setArrayLen(int len) { arrayLen = len; };
  int getArrayLen() { return arrayLen; };
  // setting the seed value again even on the same object will give the same
  // results, that's desired behavior since we want to test all algs on the same
  // data

  T *generateRandomArray() {
    T *array;
    array = (T *)malloc(arrayLen * sizeof(T));
    for (int i = 0; i < arrayLen; i++) {
      // tbc
      array[i] = rand();
    };
    if (Config::printAfterGenerating.getValue()) {
      std::cout << "------------------------" << std::endl;
      std::cout << "GENERATED ARRAY:" << std::endl;
      ;
      for (int i = 0; i < arrayLen; i++) {
        std::cout << array[i] << std::endl;
      }
      std::cout << "------------------------" << std::endl;
    }

    return array;
  };

  T *generatePartialySortedArray(double sortedPart) {
    T *array;
    array = (T *)malloc(arrayLen * sizeof(T));
    // calc length of sorted part and set this part of an array to 0s
    int sortedLen = int(sortedPart * arrayLen);
    memset(array, 0, sortedLen * sizeof(T));
    // creating rest of the array - random
    for (int i = sortedLen + 1; i < arrayLen; i++) {
      array[i] = (rand() % RAND_MAX) + 1;
    }
    if (Config::printAfterGenerating.getValue()) {
      std::cout << "------------------------" << std::endl;
      std::cout << "GENERATED ARRAY:" << std::endl;
      for (int i = 0; i < arrayLen; i++) {
        std::cout << array[i];
      }
      std::cout << "------------------------" << std::endl;
    }
    return array;
  }
  T *generateAscSortedArray() {
    T *array = generateRandomArray();
    SortingMachine<T>::quickSort(array, arrayLen);
    return array;
  }
  T *generateDscSortedArray() {
    T *array = generateRandomArray();
    SortingMachine<T>::quickSort(array, arrayLen);
    T *temp = (T *)malloc(arrayLen * sizeof(T));

    // Copy elements from original array
    // to temp in reverse order
    for (int i = 0; i < arrayLen; i++)
      temp[i] = array[arrayLen - i - 1];

    // Copy elements back to original array
    for (int i = 0; i < arrayLen; i++)
      array[i] = temp[i];
    return array;
  }

  T *readArrayFromFile() {
    T *array;
    std::ifstream testFile(Config::testFilename.getValue());
    std::string buff;
    // checking if the first line containing array len exists,
    // if not array can't be read
    if (!std::getline(testFile, buff)) {
      std::cout << "Can't read data from file "
                << Config::testFilename.getValue() << std::endl;
      return NULL;
    }
    // setting read length in config and in dataUtil class
    int length = std::stoi(buff);
    arrayLen = length;
    // reading the array
    array = (T *)malloc(length * (sizeof(T)));
    for (int i = 0; i < length; i++) {
      std::getline(testFile, buff);
      array[i] = std::stoi(buff);
    }
    if (Config::printAfterGenerating.getValue() ||
        Config::inTestMode.getValue()) {
      std::cout << "------------------------" << std::endl;
      std::cout << "READ ARRAY:" << std::endl;
      for (int i = 0; i < length; i++) {
        std::cout << array[i] << std::endl;
      }
      std::cout << "------------------------" << std::endl;
    }

    return array;
  };
};
#endif
