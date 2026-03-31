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
    array = (T *)malloc(arrayLen * (sizeof(T)));
    for (int i = 0; i < arrayLen; i++) {
      array[i] = rand();
    };
    return array;
    // TESTED: IT WORKS BUT I NEED TO KEEP TRACK OF THE ARRAY LEN
  };

  T *readArrayFromFile() {
    T *array;
    std::ifstream testFile(Config::testFilename.getValue());
    std::string buff;
    // checking if the first line containing array len exists, if not array
    // can't be read
    if (!std::getline(testFile, buff)) {
      return NULL;
    }
    std::cout << buff;
    int length = std::stoi(buff);
    array = (T *)malloc(length * (sizeof(T)));
    for (int i = 0; i < length; i++) {
      std::getline(testFile, buff);
      array[i] = std::stoi(buff);
    }
    // TBF && TBT
  };
};
