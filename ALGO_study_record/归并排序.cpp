/*
 * @Author: your name
 * @Date: 2020-04-11 18:46:07
 * @LastEditTime: 2020-04-11 18:46:28
 * @LastEditors: Please set LastEditors
 * @Description: In User Settings Edit
 * @FilePath: /algo/归并排序.cpp
 */

#include <stdio.h>
#include <iostream>
using namespace std;
int a[100];
void merge(int m[], int l, int r, int rightend);
void sort(int m[], int l, int r);
void msort();
int n;
int main() {
    cin >> n;
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
    }
    msort();
    for (int i = 0; i < n; i++) {
        cout << a[i] << " ";
    }
}

void sort(int m[], int l, int r) {
    int center;
    if (l < r) {
        center = (l + r) / 2; //这里强制类型转换直接cast调
        sort(m, l, center);
        sort(m, center + 1, r);
        merge(m, l, center + 1, r);
    }
}

void merge(int m[], int l, int r, int rightend) {
    //这里的t应该从该l开始而不是从0开始
    int t = l;
    //这里要将l保存下来
    int start = l;
    int leftend = r - 1; // r = center + 1 so, l = r - 1 = center
    // int leftend = center;
    while (l <= leftend && r <= rightend) {
        if (a[l] <= a[r]) {
            m[t++] = a[l++];
        } else {
            m[t++] = a[r++];
        }
    }
    while (l <= leftend) m[t++] = a[l++];
    while (r <= rightend) m[t++] = a[r++];

    //因为上面的l++,已经将l加到了leftend
    //这里应该从开始start 到 最后的 t 都应该修改
    for (int i = start; i < t; i++) {
        a[i] = m[i];
    }
}

void msort() {
    int temp[100];
    sort(temp, 0, n - 1);
}