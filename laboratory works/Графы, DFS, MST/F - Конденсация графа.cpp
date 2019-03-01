/*
Требуется найти количество ребер в конденсации ориентированного графа. Примечание: конденсация графа не содержит кратных ребер.

Входные данные
Первая строка входного файла содержит два натуральных числа n и m — количество вершин и ребер графа соответственно (n ≤ 10 000,  m ≤ 100 000). Следующие m строк содержат описание ребер, по одному на строке. Ребро номер i описывается двумя натуральными числами bi, ei — началом и концом ребра соответственно (1  ≤  bi,  ei  ≤  n). В графе могут присутствовать кратные ребра и петли.

Выходные данные
Единственная строка выходного файла должна содержать одно число — количество ребер в конденсации графа.
*/

#include <iostream>
#include <vector>
#include <algorithm>
#include <set>

using namespace std;

int n, m, colour = 0;
vector <vector<int>> graph, trans_graph;
vector<char> used;
vector<int> top_sort, colours;
set <int> bibib[100000];

void dfs_1 (int v) {
    used[v] = true;
    for (int i=0; i < graph[v].size(); ++i)
        if (!used[ graph[v][i] ])
            dfs_1 (graph[v][i]);
    top_sort.push_back (v);
}

void dfs_2 (int v) {
    used[v] = true;
    colours[v] = colour;
    for (int i=0; i < trans_graph[v].size(); ++i)
        if (!used[ trans_graph[v][i] ])
            dfs_2 (trans_graph[v][i]);
}

void check_1(int a, int b){
    for(int i = 0; i < graph[a].size(); i++){
        if(graph[a][i] == b){
            return;
        }
    }
    graph[a].push_back(b);
}

void check_2(int a, int b){
    for(int i = 0; i < trans_graph[a].size(); i++){
        if(trans_graph[a][i] == b){
            return;
        }
    }
    trans_graph[a].push_back(b);
}

int main(){
    cin >> n >> m;
    int a, b;
    graph.resize(n + 1);
    colours.resize(n + 1);
    trans_graph.resize(n+1);
    used.resize(n+1);
    for(int i = 0; i <= n; i++){
        used[i] = false;
    }
    for(int i = 0; i < m; i++){
        cin >> a >> b;
        if(a == b) continue;
        graph[a].push_back(b);
        trans_graph[b].push_back(a);
    }
    for(int i = 1; i <= n; i++){
        if(!used[i]){
            dfs_1(i);
        }
    }
    for(int i = 0; i <= n; i++){
        used[i] = false;
    }
    for(int i = 0; i < n; i++){
        int u = top_sort[n - 1 - i];
        if(!used[u]){
            colour++;
            dfs_2(u);
        }
    }
    for(int i = 1; i <= n; i++){
        for(int j = 0; j < graph[i].size(); j++){
            if(colours[i] != colours[graph[i][j]]){
                bibib[colours[i]].insert(colours[graph[i][j]]);
            }
        }
    }
    int ans = 0;
    for(int i = 0; i <= colour; i++) ans += bibib[i].size();
    cout << ans;
    return 0;
}