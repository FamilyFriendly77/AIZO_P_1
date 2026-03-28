#include "config.hpp"
template <typename T> class DataUtility {
private:
  int arrayLen;

public:
  DataUtility<T>();
  void setArrayLen(int len);
  T *generateRandomArray();
  T *readArrayFromFile();
};
