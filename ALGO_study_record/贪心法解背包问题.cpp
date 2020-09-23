/*
 * @Author: liukai
 * @Date: 2020-03-31 14:54:38
 * @LastEditTime: 2020-04-16 18:20:04
 * @LastEditors: liukai
 * @Description: 贪心法解决背包问题
 * @FilePath: /algo/贪心法解背包问题.cpp
 */

#include <stdlib.h>
#include <time.h>

#include <algorithm>
#include <cmath>
#include <iostream>

using std::cin;
using std::cout;

struct vwsort {
    double vw;
    int i;
};

bool cmp(vwsort a, vwsort b) { return a.vw > b.vw; }

template <typename T>
class Knapsack {
   public:
    Knapsack(const double contain) : contain{contain} {}
    Knapsack(const double contain, size_t size)
        : contain{contain}, size{size} {}

    double set_value(std::initializer_list<double> value) {
        this->value = new double[value.size()];
        this->size = value.size();
        std::copy(value.begin(), value.end(), this->value);
    }

    double set_weight(std::initializer_list<double> weight) {
        this->weight = new double[weight.size()];
        std::copy(weight.begin(), weight.end(), this->weight);
    }

    void set_value(T *value) { this->value = value; }

    void set_weight(T *weight) { this->weight = weight; }

    void init() {
        vwsort vm_sort_emp[size];
        for (int i = 0; i < size; i++) {
            vm_sort_emp[i].i = i;
            vm_sort_emp[i].vw = value[i] / weight[i];
        }
        std::sort(vm_sort_emp, vm_sort_emp + size, cmp);
        sel = new double[size];
        for(int i = 0; i < size; i ++) {
            sel[i] = 0;
        }
        int i;
        for (i = 0; weight[vm_sort_emp[i].i] < contain; i++) {
            sel[vm_sort_emp[i].i] = 1;
            total += value[vm_sort_emp[i].i];
            contain -= weight[vm_sort_emp[i].i];
        }
        sel[vm_sort_emp[i].i] = contain / weight[vm_sort_emp[i].i];
        total += sel[vm_sort_emp[i].i] * value[vm_sort_emp[i].i];
    }
    ~Knapsack() {}
    double total_value() { return total; }

    void sele() const {
        cout << "选择的物品标记1, 未选择的标记0: ";
        for (int i = 0; i < size; i++) {
            cout << sel[i] << " ";
        }
        cout << "\n";
    }

   private:
    size_t size;
    double total;
    T *value;
    T *weight;
    double *sel;
    double contain;
};

int main() {
    int container = 10;
    int size = 21;
    cout << "容量: " << container << "  大小: " << size << std::endl;
    /* cout << "输入背包容量: ";
    cin >> container; */

    Knapsack<int> kn(container, size);
    int max_value = 10;
    int min_value = 1;
    int *value = new int[container];
    int *weight = new int[container];
    srand((unsigned)time(NULL));
    for (int i = 0; i < size; i++) {
        value[i] = rand() % (max_value - min_value) + min_value;
        weight[i] = rand() % (max_value - min_value) + min_value;
    }

    cout << "价值: ";
    for (int i = 0; i < size; i++) {
        cout << value[i] << " ";
        // weight[i] = rand() % (max_value - min_value);
    }
    cout << std::endl;

    cout << "重量: ";
    for (int i = 0; i < size; i++) {
        cout << weight[i] << " ";
        // weight[i] = rand() % (max_value - min_value);
    }
    cout << std::endl;

    /* kn.set_value({3, 4, 7});
    kn.set_weight({1, 2, 3}); */

    kn.set_value(value);
    kn.set_weight(weight);
    kn.init();
    kn.sele();
    cout << "最大价值: " << kn.total_value() << std::endl;
    return 0;
}