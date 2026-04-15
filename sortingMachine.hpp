#ifndef SORTINGMACHINE_HPP
#define SORTINGMACHINE_HPP
#include "config.hpp"
#include <algorithm>
#include <ctime>
#include <random>
template <typename T> class SortingMachine {
private:
  static inline std::mt19937 pivotGenerator{
      static_cast<unsigned int>(time(nullptr))};
  static inline std::uniform_real_distribution<double> generatePivot{0, 1.0};

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
  static void heapify(T *arr, int len, int index) {
    int left = index * 2 + 1;
    int right = index * 2 + 2;
    int newRootI = index;
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
  static void heapSort(T *arr, int len) {
    for (int i = len / 2 - 1; i >= 0; i--)
      heapify(arr, len, i);

    int heapSize = len - 1;
    while (heapSize > 0) {
      std::swap(arr[0], arr[heapSize]);
      heapify(arr, heapSize, 0);
      heapSize--;
    }
  }
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
      pIndex = (int)(generatePivot(pivotGenerator) * len);
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
  static void shellSortOne(T *arr, int len) {
    // Macin Ciura: Best Increments for the Average Case of Shellsort

    int gaps[] = {1, 4, 10, 23, 57, 132, 301, 701};
    int i = 0;

    while (i < 8 && gaps[i] < len) {
      i++;
    }
    i--;
    if (i == 0)
      return;
    while (i >= 0) {
      for (int j = gaps[i]; j < len; j++) {
        T temp = arr[j];
        int k = j;

        while (k >= gaps[i] && arr[k - gaps[i]] > temp) {
          arr[k] = arr[k - gaps[i]];
          k -= gaps[i];
        }
        arr[k] = temp;
      }
      i--;
    }
  };
  static void shellSortTwo(T *arr, int len) {
    int gap = 1;
    while (gap <= len / 2)
      gap = gap * 2 + 1;
    for (; gap >= 1; gap /= 2) {
      for (int i = gap; i < len; i++) {
        T temp = arr[i];
        int j = i;

        while (j >= gap && arr[j - gap] > temp) {
          arr[j] = arr[j - gap];
          j -= gap;
        }
        arr[j] = temp;
      }
    }
  };
};
#endif
