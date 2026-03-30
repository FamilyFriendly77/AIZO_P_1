#include <chrono>
#include <cstring>
#include <functional>
template <typename T> class TestingUtility {
private:
  int repetitionsCounter;

public:
  void setRepetitionsCounter(int counter) { repetitionsCounter = counter; };
  void testSortingTime(std::function<void(T *, int)> sort, T *arr, int arrLen) {
    for (int i = 0; i < repetitionsCounter; i++) {
      T *arrCpy;
      std::memcpy(arrCpy, arr, sizeof(arr));
    }
  };
};
