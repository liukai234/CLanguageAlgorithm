/*
 * @Author: your name
 * @Date: 2020-03-31 09:00:46
 * @LastEditTime: 2020-04-01 16:46:52
 * @LastEditors: Please set LastEditors
 * @Description: 蛮力法解决凸包问题
 * @FilePath: /algo/hull.cpp
 */

#include <stdlib.h>
#include <time.h>

#include <iostream>
#include <set>
using namespace std;

constexpr int maxn = 10005;

typedef struct Point {
    int x;
    int y;
} point;

set<pair<int, int>> s;

class Convexhull {
   public:
    Convexhull(int n) : n{n} {}
    void cop() {
        s.clear();
        if (n < 3) {
            return;
        }
        // cout << "输入顶点坐标: ";
        // 随机生成坐标
        for (int i = 0; i < n; i++) cin >> p[i].x >> p[i].y;
        if (n == 3) {
            if (judge(p[0], p[1], p[2]) != 2 || judge(p[0], p[2], p[1]) != 2 ||
                judge(p[1], p[2], p[0]) != 2) {
                for (int i = 0; i < n; i++) {
                    s.insert(make_pair(p[i].x, p[i].y));
                }
                return;
            }
        }
        for (int i = 0; i < n; i++) {
            int t = 0;
            for (int j = 0; j < n; j++) {
                int flag = -1;
                if (i == j) continue;
                for (int k = 0; k < n; k++) {
                    if (k == i || k == j) continue;
                    if (flag == -1) {
                        flag = judge(p[i], p[j],
                                     p[k]);  // 如果只有三个点则t不能被刷新
                    } else {
                        int temp = judge(p[i], p[j], p[k]);
                        if (flag == temp || temp == 2)
                            t = 1;
                        else {
                            t = 0;
                            break;
                        }
                    }
                }
                if (t) s.insert(make_pair(p[j].x, p[j].y));
            }
        }
    }

   private:
    int n;
    point p[maxn];
    int judge(point p1, point p2, point p3) {
        int flag = p1.x * p2.y + p3.x * p1.y + p2.x * p3.y - p3.x * p2.y -
                   p2.x * p1.y - p1.x * p3.y;
        if (flag > 0) {  // 左侧
            return 1;
        } else if (flag == 0) {  //在线上
            return 2;
        } else {
            return 0;  // 右侧
        }
    }
};

int main() {
    srand((unsigned)time(NULL));
    for (int i = 0; i < 10; i++) cout << rand() << '\t';
    cout << endl;

    cout << "输入顶点个数: ";
    int n;
    cin >> n;
    Convexhull hull(n);
    hull.cop();
    if (!s.empty()) {
        cout << "能构成凸包的顶点: ";
        for (auto x : s) {
            cout << "(" << x.first << "," << x.second << ") ";
        }
        cout << endl;
    } else {
        cout << "不能构成凸包\n";
    }
    return 0;
}