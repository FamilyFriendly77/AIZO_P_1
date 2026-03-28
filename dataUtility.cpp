#include "dataUtility.hpp"
#include <cstdlib>
#include <fstream>
#include <iostream>
#define RAND_MAX INT_MAX
template <typename T> DataUtility<T>::DataUtility() {
  arrayLen = Config::testArrayLen.getValue();
  unsigned int randomSeed = Config::randomSeed.getValue();
};
template <typename T> void DataUtility<T>::setArrayLen(int len) {
  arrayLen = len;
}

template <typename T> T *DataUtility<T>::generateRandomArray() {
  T *array;
  array = (T *)malloc(arrayLen * (sizeof(T)));
  for (int i = 0; i < arrayLen; i++) {
    array[i] = rand();
  };
  for (int i = 0; i < arrayLen; i++)
    return array;
}

template <typename T> T *DataUtility<T>::readArrayFromFile() {
  T *array;
  std::ifstream testFile(Config::testFilename.getValue());
}
