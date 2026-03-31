#include <chrono>
template <typename T> class TestingUtility {
private:
  int repetitionsCounter = 1;

public:
  void setRepetitionsCounter(int counter) { repetitionsCounter = counter; };
  template <typename Func> void testSortingTime(Func sort, T *arr, int arrLen) {
    std::chrono::duration<double> total_time(0);
    for (int i = 0; i < repetitionsCounter; i++) {
      T *arrCpy = (T *)malloc(sizeof(T) * arrLen);
      std::memcpy(arrCpy, arr, sizeof(T) * arrLen);
      auto start = std::chrono::high_resolution_clock::now();
      sort(arrCpy, arrLen);
      auto end = std::chrono::high_resolution_clock::now();
      total_time += (end - start);
    }
    double averageSeconds = total_time.count() / repetitionsCounter;
    std::cout << averageSeconds / repetitionsCounter;
  };
};
