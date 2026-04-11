#ifndef SORTINGMACHINE_HPP
#define SORTINGMACHINE_HPP
#include "config.hpp"
#include <algorithm>

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
  void heapify(T *arr, int len, int index) {
    int left = index * 2 + 1;
    int right = index * 2 + 2;
    int newRootI = index;
    if (arr[index] > arr[left] && arr[index] > arr[right]) {
      return;
    }
    if (left < len && arr[left] > arr[newRootI]) {
      newRootI = left;
    }
    if (right < len && arr[right] > arr[newRootI]) {
      newRootI = right;
    }
    if (newRootI != index) {
      std::swap(arr[index], arr[newRootI]);
      heapify(arr, len, newRootI);
    }
  }
  void heapSort(T *arr, int len) {}
  static void quickSort(T *arr, int len) {
    PivotStrategy pivotStrat = Config::quickSortPivot.getValue();
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
    quickSort(arr, i);
    quickSort(arr + i + 1, len - i - 1);
  }
  void shellSort(T *arr);
};
#endif
