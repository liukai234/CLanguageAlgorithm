/*
 * @Author: your name
 * @Date: 2020-04-11 18:45:15
 * @LastEditTime: 2020-04-11 18:45:50
 * @LastEditors: Please set LastEditors
 * @Description: In User Settings Edit
 * @FilePath: /algo/预排序.cpp
 */
#include <iostream>
constexpr int MAX = 100;
using std::cout;

int arr[MAX];

void sort(int *arr, int l, int r);
bool PersortElementUniqueness(int *A, int n);
int statmode(int *A, int n);
int main() {
    int n = 3;
    std::cin >> n;

    for (int i = 0; i < n; i++) {
        std::cin >> arr[i];
    }
    /* arr[0] = 1;
    arr[1] = 4;
    arr[2] = 2; */
    sort(arr, 0, n - 1);

    for (int i = 0; i < n; i++) {
        cout << arr[i] << " ";
    }
    cout << std::endl;
    if (PersortElementUniqueness(arr, n)) {
        cout << "not repeat" << std::endl;
    } else {
        cout << "repeat" << std::endl;
    }
    // 这样进行模式计算的问题, 首元素不确定是不是模 的问题 就难以处理
    cout << "mode: " << statmode(arr, n) << std::endl;
}

// 对预排许的数组检查重复元素的个数,
// 即求列表的模"在整型列表中重复出现次数最多的值"
int statmode(int *A, int n) {
    int i = 0;
    int modestat = 0;
    int modeval = 0;
    while (i < n) {
        int curlength = 0;
        int curval = A[i];
        while (i + curlength < n && A[i + curlength] == curval) {
            ++curlength;
        }
        if (curlength > modestat) {
            modestat = curlength;
            modeval = curval;
        }
        i += curlength;
    }
    return modeval;
}

// 对预排序的数组检查唯一性
bool PersortElementUniqueness(int *A, int n) {
    // 对数组排序
    for (int i = 0; i < n - 1; i++) {
        if (A[i] == A[i + 1]) return false;
    }
    return true;
}

void mergeSort(int *arr, int l, int r, int center) {
    int lstart = l;
    int lend = center;
    int rstart = center + 1;
    int rend = r;

    int temp[MAX];
    int t = l;

    while (lstart <= lend && rstart <= rend) {
        if (arr[lstart] <= arr[rstart]) {
            temp[t++] = arr[lstart++];
        } else {
            temp[t++] = arr[rstart++];
        }
    }
    while (lstart <= lend) temp[t++] = arr[lstart++];
    while (rstart <= rend) temp[t++] = arr[rstart++];

    for (int i = l; i <= r; i++) {  // 累计到 <= r
        arr[i] = temp[i];
    }
}

void sort(int *arr, int l, int r) {
    if (l < r) {
        int center = (l + r) / 2;
        sort(arr, l, center);
        sort(arr, center + 1, r);
        mergeSort(arr, l, r, center);
    }
}
