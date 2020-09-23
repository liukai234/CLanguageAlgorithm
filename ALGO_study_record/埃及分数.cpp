/*
 * @Author: your name
 * @Date: 2020-04-11 18:44:48
 * @LastEditTime: 2020-04-11 18:44:59
 * @LastEditors: Please set LastEditors
 * @Description: In User Settings Edit
 * @FilePath: /algo/埃及分数.cpp
 */

#include <cmath>
#include <iostream>

using namespace std;

int maxComDiv(int a, int b);
int main() {
    cout << "molecule: ";
    int a;

    cin >> a;
    int b;
    cout << "denominator: ";
    cin >> b;
    int e;

    //要求是如果分子大于1就可以拆分
    do {
        e = b / a + 1;
        cout << "1/" << e << endl;

        a = a * e - b;
        b = b * e;

        int maxDiv = maxComDiv(a, b);
        if (maxDiv > 1) {
            a /= maxDiv;
            b /= maxDiv;
        }
    } while (a > 1);
    cout << "1/" << b << endl;
}

int maxComDiv(int a, int b) {
    int temp = 0;
    while (b != 0) {
        temp = a % b;
        a = b;
        b = temp;
    }
    return a;
}
