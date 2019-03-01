/*
Компонентой вершинной двусвязности графа  называется максимальный по включению подграф (состоящий из вершин и ребер), 
такой что любые два ребра из него лежат на вершинно простом цикле.

Дан неориентированный граф без петель. Требуется выделить компоненты вершинной двусвязности в нем.

Входные данные
Первая строка входного файла содержит два натуральных числа n и m — количества вершин и ребер графа соответственно (1 ≤ n ≤ 20 000, 1 ≤ m ≤ 200 000).

Следующие m строк содержат описание ребер по одному на строке. 
Ребро номер i описывается двумя натуральными числами bi, ei — номерами концов ребра (1 ≤ bi, ei ≤ n).

Выходные данные
В первой строке выходного файла выведите целое число k — количество компонент вершинной двусвязности графа. 
Во второй строке выведите m натуральных чисел a1, a2, ..., am, не превосходящих k, где ai — номер компоненты вершинной двусвязности, которой принадлежит i-е ребро. Ребра нумеруются с единицы в том порядке, в котором они заданы во входном файле.
*/

#include <iostream>
#include <vector>
#include <algorithm>
#include <iostream>
#include <cmath>

using namespace std;

int n, m, timer = 0, colour = 0;
vector < vector <pair<int, int>>> graph;
vector <bool> used, soch;
vector <int> timein, fun, colours;

bool dfs (int v, int parent) {
    used[v] = true;
    timein[v] = timer++;
    fun[v] = timein[v];
    int ch = 0;
    for (int i = 0; i < graph[v].size(); ++i) {
        int to = graph[v][i].first;
        if (to == parent)  continue;
        if (used[to])
            fun[v] = min (fun[v], timein[to]);
        else
            dfs (to, v);
        fun[v] = min (fun[v], fun[to]);
        ch++;
    }
}

void diff(int v, int col, int parent){
    used[v] = true;
    for(int i = 0; i < graph[v].size(); i++){
        int u = graph[v][i].first;
        if(u == parent) continue;
        if(!used[u]){
            if(fun[u] >= timein[v]){
                int nCol = ++colour;
                for(int j = 0; j < graph[v].size(); j++){
                    if(u == graph[v][j].first){
                        colours[graph[v][j].second] = nCol;
                    }
                }
                diff(u, nCol, v);
            }else{
                for(int j = 0; j < graph[v].size(); j++){
                    if(u == graph[v][j].first){
                        colours[graph[v][j].second] = col;
                    }
                }
                diff(u, col, v);
            }
        }else if(timein[u] < timein[v]){
            for(int j = 0; j < graph[v].size(); j++){
                    if(u == graph[v][j].first){
                        colours[graph[v][j].second] = col;
                    }
            }
        }
    }
}

int main(){
    cin >> n >> m;
    int a, b;
    graph.resize(n + 1);
    used.resize(n+1);
    soch.resize(n + 1);
    timein.resize(n+1);
    fun.resize(n+1);
    for(int i = 0; i < m; i++){
        cin >> a >> b;
        graph[a].push_back(make_pair(b, i));
        graph[b].push_back(make_pair(a, i));
    }
    colours.resize(m);
    for(int i = 0; i <= n; i++){
        used[i] = false;
        soch[i] = false;
    }
    for(int i = 1; i <= n; i++){
        if(!used[i]){
            dfs(i, -1);
        }
    }
    for(int i = 1; i <= n; i++){
        used[i] = false;
    }
    for(int i = 1; i <= n; i++){
        if(!used[i]){
            diff(i, colour, -1);
        }
    }
    cout << colour << endl;
    for(int i = 0; i < m; i++){
        cout << colours[i]<< " ";
    }
    return 0;
}