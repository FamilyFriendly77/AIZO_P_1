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
  void quickSort(T *arr);
  void shellSort(T *arr);
};
