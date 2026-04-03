#include "config.hpp"
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <string>
#define RAND_MAX INT_MAX

template <typename T> class DataUtility {
private:
  int arrayLen;

public:
  DataUtility<T>() {
    arrayLen = Config::testArrayLen.getValue();
    unsigned int randomSeed = Config::randomSeed.getValue();
  };
  void setArrayLen(int len) { arrayLen = len; };
  T *generateRandomArray() {
    T *array;
    array = (T *)malloc(arrayLen * sizeof(T));
    for (int i = 0; i < arrayLen; i++) {
      array[i] = rand();
    };
    if (Config::printAfterSorting.getValue()) {
      for (int i = 0; i < arrayLen; i++) {
        std::cout << array[i];
      }
    }

    return array;
  };

  T *generatePartialySortedArray(double sortedPart) {
    T *array;
    array = (T *)malloc(arrayLen * sizeof(T));
    int sortedLen = int(sortedPart * arrayLen);
    memset(array, 0, sortedLen * sizeof(T));
    for (int i = sortedLen + 1; i < arrayLen; i++) {
      array[i] = rand();
    }
    if (Config::printAfterSorting.getValue()) {
      for (int i = 0; i < arrayLen; i++) {
        std::cout << array[i];
      }
    }
  }

  T *readArrayFromFile() {
    T *array;
    std::ifstream testFile(Config::testFilename.getValue());
    std::string buff;
    // checking if the first line containing array len exists, if not array
    // can't be read
    if (!std::getline(testFile, buff)) {
      std::cout << "Can't read data from file "
                << Config::testFilename.getValue() << std::endl;
      return NULL;
    }
    int length = std::stoi(buff);
    arrayLen = length;
    Config::testArrayLen.setSetting(length);

    array = (T *)malloc(length * (sizeof(T)));
    for (int i = 0; i < length; i++) {
      std::getline(testFile, buff);
      array[i] = std::stoi(buff);
    }
    if (Config::printAfterSorting.getValue()) {
      for (int i = 0; i < length; i++) {
        std::cout << array[i];
      }
    }

    return array;
  };
};
