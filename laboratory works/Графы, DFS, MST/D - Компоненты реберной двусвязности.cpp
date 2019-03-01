/*
Компонентой реберной двусвязности графа  называется подмножество вершин , такое что для любых различных u и v из этого множества существует не менее двух реберно не пересекающихся путей из u в v.

Дан неориентированный граф. Требуется выделить компоненты реберной двусвязности в нем.

Входные данные
Первая строка входного файла содержит два натуральных числа n и m — количества вершин и ребер графа соответственно (1  ≤  n  ≤  20 000, 1  ≤  m  ≤  200 000).

Следующие m строк содержат описание ребер по одному на строке. 
Ребро номер i описывается двумя натуральными числами bi, ei — номерами концов ребра (1 ≤ bi, ei ≤ n).

Выходные данные
В первой строке выходного файла выведите целое число k — количество компонент реберной двусвязности графа. 
Во второй строке выведите n натуральных чисел a1, a2, ..., an, не превосходящих k, где ai — номер компоненты реберной двусвязности, которой принадлежит i-я вершина.
*/

#include <iostream>
#include <vector>
#include <algorithm>
#include <iostream>
#include <cmath>

using namespace std;

int n, m, timer = 0, colour = 0;
vector < vector <pair<int, int>>> graph;
vector <bool> used;
vector <int> timein, fun, colours;

void dfs_2(int v, int col){
    colours[v] = col;
    for (int i=0; i < graph[v].size(); ++i) {
        int to = graph[v][i].first;
        if (colours[to] == 0){
            if((fun[to] > timein[v] || fun[v] > timein[to]) && graph[v][i].second == 1){
                colour++;
                dfs_2(to, colour);
            }else dfs_2(to, col);
        }
}
}


void dfs_1 (int v, int parent) {
    used[v] = true;
    timein[v] = timer++;
    fun[v] = timein[v];
    for (int i=0; i < graph[v].size(); ++i) {
        int to = graph[v][i].first;
        if (to == parent)  continue;
        if (used[to])
            fun[v] = min (fun[v], timein[to]);
        else {
            dfs_1 (to, v);
            fun[v] = min (fun[v], fun[to]);
        }
}
}

void check(int a, int b){
    for(int i = 0; i < graph[a].size(); i++){
        if(graph[a][i].first == b){
            graph[a][i].second++;
            return;
        }
    }
    pair <int, int> p;
    p.first = b;
    p.second = 1;
    graph[a].push_back(p);
}

int main(){
    cin >> n >> m;
    int a, b;
    graph.resize(n + 1);
    used.resize(n+1);
    colours.resize(n + 1);
    timein.resize(n+1);
    fun.resize(n+1);
    for(int i = 0; i <= n; i++){
        used[i] = false;
        colours[i] = 0;
    }
    for(int i = 0; i < m; i++){
        cin >> a >> b;
        check(a, b);
        check(b, a);
    }
    for(int i = 1; i <= n; i++){
        if(!used[i]){
            dfs_1(i, -1);
        }
    }
    for(int i = 1; i <= n; i++){
        if(colours[i] == 0){
            colour++;
            dfs_2(i, colour);
        }
    }

    cout << colour << endl;
    for(int i = 1; i <= n; i++){
        cout << colours[i] << " ";
    }
    return 0;
}