#include "sortingMachine.hpp"
template <typename T> void SortingMachine<T>::insertSort(T *arr, int n) {
  for (int i = 1; i < n; i++) {
    int val = &arr[i];
    int j = i - 1;

    while (j >= 0 and &arr[j] > val) {
      &arr[j + 1] = &arr[j];
      j--;
    }
    &arr[j + 1] = val;
  }
}
template <typename T> void SortingMachine<T>::heapSort(T *arr) {}
template <typename T> void SortingMachine<T>::shellSort(T *arr) {}
template <typename T> void SortingMachine<T>::quickSort(T *arr) {}
