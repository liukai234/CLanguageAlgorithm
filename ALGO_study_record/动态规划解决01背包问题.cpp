/*
 * @Author: your name
 * @Date: 2020-04-02 09:31:06
 * @LastEditTime: 2020-04-13 11:38:00
 * @LastEditors: liukai
 * @Description: In User Settings Edit
 * @FilePath: /algo/动态规划解决01背包问题.cpp
 */
#include <stdlib.h>
#include <time.h>

#include <iostream>

using namespace std;

class package0_1 {
   public:
    package0_1(int **const m, int *const w, int *const v, const int n,
               const int c)
        : m{m}, w{w}, v{v}, n{n}, c{c} {
        //采用从底到顶的顺序来设置m[i][j]的值
        //首先放w[n]
        for (int j = 0; j <= c; j++)
            if (j < w[n])
                m[n][j] = 0;  // j小于w[n],所对应的值设为0，否则就为可以放置
            else
                m[n][j] = v[n];

        //对剩下的n-1个物品进行放置。
        int i;
        for (i = n - 1; i >= 1; i--)
            for (int j = 0; j <= c; j++)
                if (j < w[i]) m[i][j] = m[i + 1][j];
                //如果j <
                // w[i]则，当前位置就不能放置，它等于上一个位置的值。否则，就比较到底是放置之后的值大，还是不放置的值大，选择其中较大者。
                else
                    m[i][j] = m[i + 1][j] > m[i + 1][j - w[i]] + v[i]
                                  ? m[i + 1][j]
                                  : m[i + 1][j - w[i]] + v[i];
    }

    void answer(int *const x) {
        int j = c;
        int i;
        for (i = 1; i <= n - 1; i++)
            if (m[i][j] == m[i + 1][j])
                x[i] = 0;
            else {
                x[i] = 1;
                j = j - w[i];
            }
        x[n] = m[i][j] ? 1 : 0;
    }

   private:
    int **m;
    int *w;
    int *v;
    const int n;
    const int c;
};

int main() {
    const int c = 10;  //背包容量
    const int n = 5;  // 物品个数
    int *w = new int[n];
    int *v = new int[n];
    int x[n + 1];
    for(int i = 0; i <= n + 1; i ++) {
        x[i] = 0;
    }
    int max_value = 10;
    int min_value = 1;
    srand((unsigned)time(NULL));
    for (int i = 1; i <= n; i++) {
        v[i] = rand() % (max_value - min_value) + min_value;
        w[i] = rand() % (max_value - min_value) + min_value;
    }
    /* int v[n + 1] = {0, 6, 3, 5, 4, 6};
    int w[n + 1] = {0, 2, 2, 6, 5, 4}; */
    for (int i = 1; i <= n; i++) {
        cout << v[i] << " ";
    }
    cout << endl;
    for (int i = 1; i <= n; i++) {
        cout << w[i] << " ";
    }
    cout << endl;
    int **m;
    m = new int *[n + 1];
    for (int i = 0; i < n + 1; ++i) {
        m[i] = new int[c + 1];
    }

    for (int i = 0; i <= n; i++) {
        for (int j = 0; j <= c; j++) {
            m[i][j] = 0;
        }
    }

    package0_1 pack(m, w, v, n, c);
    for (int i = 0; i <= n; i++) {
        for (int j = 0; j <= c; j++) printf("%2d ", m[i][j]);
        cout << endl;
    }

    cout << "最大价值为: " << m[1][c] << endl;
    pack.answer(x);

    cout << "最优解为: ";
    for (int i = 1; i <= n; i++) cout << x[i] << " ";
    cout << endl;
    // delete[] w;
    // delete[] v;
    for (int i = 0; i <= n; ++i) {
        delete[] m[i];
    }
    delete[] m;
    return 0;
}