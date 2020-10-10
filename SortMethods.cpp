//
// Created by xcmworkharder on 2020-10-10 上午8:10.
//
#include <iostream>
#include <vector>

using namespace std;

/// 归并排序
void merge(vector<int>& arr, int left, int mid, int right) {
    vector<int> tmp(arr.begin() + left, arr.begin() + right + 1); // 此处需要right + 1,否则却不到最后一个元素
    int i = left, j = mid + 1;
    int index = left;
    while (i <= mid && j <= right) {
        if (tmp[i - left] <= tmp[j - left]) {
            arr[index++] = tmp[i - left];
            i++;
        } else {
            arr[index++] = tmp[j - left];
            j++;
        }
    }
    while (i <= mid) {
        arr[index++] = tmp[i - left];
        i++;
    }
    while (j <= right) {
        arr[index++] = tmp[j - left];
        j++;
    }
}

void mergeSort(vector<int>& arr, int left, int right) {
    if (left >= right) {
        return;
    }

    int mid = left + (right - left) / 2;
    mergeSort(arr, left, mid);
    mergeSort(arr, mid + 1, right);
    if (arr[mid] > arr[mid + 1]) {
        merge(arr, left, mid, right);
    }
}

void mergeSort(vector<int>& arr) {
    mergeSort(arr, 0, arr.size() - 1);
}

/// 快速排序
vector<int> partition(vector<int>& arr, int left, int right) {
    swap(arr[left], arr[left + (rand() % (right - left + 1))]);
    int pivot = arr[left];
    int low = left, high = right;
    int index = left; // [left, low), index>=low index <= high (high, right]
    while (index <= high) {
        if (arr[index] < pivot) {
            swap(arr[index++], arr[low++]);
        } else if (arr[index] > pivot) {
            swap(arr[index], arr[high--]);
        } else {
            index++;
        }
    }
    return vector<int>{low, high};
}

void quickSort(vector<int>& arr, int left, int right) {
    if (left >= right) {
        return;
    }

    vector<int> index = partition(arr, left, right);
    quickSort(arr, left, index[0] - 1);
    quickSort(arr, index[1] + 1, right);
}

void quickSort(vector<int>& arr) {
    srand(time(nullptr));
    quickSort(arr, 0, arr.size() - 1);
}

/// 插入排序
void insertSort(vector<int>& arr) {
    int n = arr.size();
    if (n == 0) {
        return;
    }
    for (int i = 1; i < n; ++i) {
        int j = 0;
        int curValue = arr[i];
        for(j = i; j > 0 && arr[j - 1] > curValue; j--) {
            arr[j] = arr[j - 1];
        }
        arr[j] = curValue;
    }
}

/// 带左右边界的插入排序
void insertSort(vector<int>& arr, int left, int right) {
    if (left >= right) {
        return;
    }
    for (int i = left + 1; i <= right; ++i) {
        int j = 0;
        int curValue = arr[i];
        for (j = i; j > left && arr[j - 1] > curValue; j--) {
            arr[j] = arr[j - 1];
        }
        arr[j] = curValue;
    }
}

/// 选择排序
void selSort(vector<int>& arr) {
    int n = arr.size();
    if (n == 0) {
        return;
    }
    for (int i = 0; i < n; ++i) {
        int minIndex = i;
        for (int j = i + 1; j < n; ++j) {
            if (arr[j] < arr[minIndex]) {
                minIndex = j;
            }
        }
        swap(arr[i], arr[minIndex]);
    }
}

/// 冒泡排序
void bubbleSort(vector<int>& arr) {
    int n = arr.size();
    if (n == 0) {
        return;
    }
    int endIndex = n - 1;
    while (true) {
        bool isSorted = true;
        for (int i = 0; i < endIndex; ++i) {
            if (arr[i] > arr[i + 1]) {
                swap(arr[i], arr[i + 1]);
                isSorted = false;
            }
        }
        endIndex--;
        // 如果发现单次已经没有冒泡，说明已经有序，可以提前退出排序
        if (isSorted) {
            break;
        }
    }
}

int main() {

    vector<int> arr{30, 10000, 1000, 3, 2000, 5, 4, 6};
    //mergeSort(arr);
    //quickSort(arr);
    //insertSort(arr, 1, 3);
    //selSort(arr);
    bubbleSort(arr);
    for (auto& a : arr) {
        cout << a << " ";
    }

    return 0;
}



