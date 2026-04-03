#ifndef SORTINGMACHINE_HPP
#define SORTINGMACHINE_HPP
#include <algorithm>
enum PivotStrategy { FIRST, LAST, MIDDLE, RANDOM };

template <typename T> class SortingMachine {
public:
  static void insertSort(T *arr, int len) {
    for (int i = 1; i < len; i++) {
      int val = arr[i];
      int j = i - 1;

      while (j >= 0 and arr[j] > val) {
        arr[j + 1] = arr[j];
        j--;
      }
      arr[j + 1] = val;
    }
  }
  void heapSort(T *arr);
  void quickSort(T *arr, int len, PivotStrategy pivotStrat) {
    int pIndex;
    switch (pivotStrat) {
    case FIRST:
      pIndex = 0;
      break;
    case LAST:
      pIndex = len - 1;
      break;
    case MIDDLE:
      pIndex = len / 2;
      break;
    case RANDOM:
      // tbf
      pIndex = 0;
      break;
    }
    if (len <= 1)
      return;
    T pivot = arr[pIndex];
    std::swap(arr[pIndex], arr[len - 1]);
    int i = 0;
    int j = len - 2;
    while (i <= j) {
      if (arr[i] < pivot) {
        i++;
      } else if (arr[j] > pivot) {
        j--;
      } else {
        std::swap(arr[i], arr[j]);
        i++;
        j--;
      }
    }
    std::swap(arr[i], arr[len - 1]);
    quickSort(arr, i, pivotStrat);
    quickSort(arr + i + 1, len - i - 1, pivotStrat);
  }
  void shellSort(T *arr);
};
#endif
