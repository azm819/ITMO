/*
Дан ориентированный невзвешенный граф. Необходимо его топологически отсортировать.

Входные данные
В первой строке входного файла даны два натуральных числа N и M (1 ≤ N ≤ 100 000, 0 ≤ M ≤ 100 000) — количество вершин и рёбер в графе соответственно. 
Далее в M строках перечислены рёбра графа. Каждое ребро задаётся парой чисел — номерами начальной и конечной вершин соответственно.

Выходные данные
Вывести любую топологическую сортировку графа в виде последовательности номеров вершин. 
Если граф невозможно топологически отсортировать, вывести -1.
*/

#include <iostream>
#include <vector>
#include <algorithm>
#include <iostream>
#include <cmath>

using namespace std;
int n, m;
vector < vector <int>> g;
vector <int> used;
vector <int> ans;

bool dfs (int v) {
    used[v] = 1;
    bool t = true;
    for (size_t i = 0; i < g[v].size(); ++i) {
        int to = g[v][i];
        if (used[to] == 0){
            t = dfs(to);
            if (!t) return false;
        }
        if(used[to] == 1){
            return false;
        }
    }
    used[v] = 2;
    ans.push_back(v);
    return t;
}

bool topological_sort() {
    for (int i = 1; i <= n; ++i)
        used[i] = 0;
    ans.clear();
    bool t;
    for (int i = 1; i <= n; ++i){
        if (used[i] == 0){
            t = dfs(i);
            if(!t) return false;
        }
    }
    reverse (ans.begin(), ans.end());
    return true;
}

int main(){
    cin >> n >> m;
    int a, b;
    g.resize(n + 1);
    used.resize(n+1);
    for(int i = 0; i < m; i++){
        cin >> a >> b;
        g[a].push_back(b);
    }
    bool t = topological_sort();
    if(t){
        for(int i = 0; i < n; i++){
            cout << ans[i] << " ";
        }
    }
    else{
        cout << -1;
    }
    return 0;
}
