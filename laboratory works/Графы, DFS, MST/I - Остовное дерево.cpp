/*
Даны точки на плоскости, являющиеся вершинами полного графа. Вес ребра равен расстоянию между точками, соответствующими концам этого ребра. 
Требуется в этом графе найти остовное дерево минимального веса.

Входные данные
Первая строка входного файла содержит натуральное число n — количество вершин графа (1 ≤ n ≤ 10 000). 
Каждая из следующих n строк содержит два целых числа xi, yi  — координаты i-й вершины ( - 10 000 ≤ xi, yi ≤ 10 000). 
Никакие две точки не совпадают.

Выходные данные
Первая строка выходного файла должна содержать одно вещественное число — вес минимального остовного дерева.

#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

struct versh{
    double x = 0, y = 0;
};

const double INF = 1000000000;

int n;
vector <versh> ver;
vector <double> min_e;
vector <bool> used;

double find_d(versh a, versh b){
    int x = a.x - b.x;
    int y = a.y - b.y;
    return sqrt(x*x + y*y);
}



int main(){
    cin >> n;
    ver.resize(n);
    min_e.resize(n);
    used.resize(n);
    double a, b;
    for(int i = 0; i < n; i++){
        used[i] = false;
        cin >> a >> b;
        min_e[i] = INF;
        ver[i].x = a;
        ver[i].y = b;
    }
    min_e[0] = 0;
    double ans = 0;
    for (int i = 0; i < n; i++) {
        int v = -1;
        for (int j = 0; j < n; j++)
            if (!used[j] && (v == -1 || min_e[j] < min_e[v]))
                v = j;
        used[v] = true;
        ans += min_e[v];
        for (int j = 0; j < n; j++){
            float d = find_d(ver[v], ver[j]);
            if (d < min_e[j]) {
                min_e[j] = d;
            }
        }
    }
    cout << ans;
    return 0;
}