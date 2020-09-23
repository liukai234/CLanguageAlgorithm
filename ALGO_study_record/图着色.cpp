/*
 * @Author: your name
 * @Date: 2020-03-30 08:52:12
 * @LastEditTime: 2020-03-31 08:52:14
 * @LastEditors: Please set LastEditors
 * @Description: 图着色
 * @FilePath: /algo/test.cpp
 */
#include <iostream>
using namespace std;

int n;
int color[100];
int arc[10][10];  //无向连通图

int OK(int i) {
    // 检测所有在无向图存储的矩阵中与i点相邻的点颜色不冲突, 有相邻点时标记为arc[i][j] = 1
    for (int j = 0; j < n; j++)
        if (arc[i][j] == 1 && color[i] == color[j]) return 0;
    return 1;
}

int colorgraph() {
    int k = 0;
    int flag = 1; // 只要连通图还未填充完, 则flag一定为1
    while (flag == 1) {
        k++;
        flag = 0;
        for (int i = 0; i < n; i++) {
            if (color[i] == 0) {
                color[i] = k;
                if (!OK(i)) {
                    color[i] = 0;
                    flag = 1; // 没填充完一定会进这里
                }
            }
        }
    }
    return k;
}


int main() {

    int v;
    int a, b;
    cin >> n; // 顶点
    cin >> v; // 边数
    
    // 初始化图
    for (int i = 0; i < v; i++) {
        cin >> a >> b;
        arc[a][b] = 1;
        arc[b][a] = 1;
    }
    
    cout << "最少着色数 k = " << colorgraph() << endl;
}