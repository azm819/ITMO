/*
Вам дан взвешенный ориентированный граф и вершина s в нём. Для каждой вершины графа u выведите длину кратчайшего пути от вершины s до вершины u.

Входные данные
Первая строка входного файла содержит три целых числа n, m, s — количество вершин и ребёр в графе и номер начальной вершины соответственно (2 ≤ n ≤ 2 000, 1 ≤ m ≤ 5 000).

Следующие m строчек описывают рёбра графа. Каждое ребро задаётся тремя числами — начальной вершиной, конечной вершиной и весом ребра соответственно. Вес ребра — целое число, не превосходящее 1015 по абсолютной величине. В графе могут быть кратные рёбра и петли.

Выходные данные
Выведите n строчек — для каждой вершины u выведите длину кратчайшего пути из s в u. Если не существует пути между s и u, выведите «*». Если не существует кратчайшего пути между s и u, выведите «-».
*/

#include <fstream>
#include <vector>
#include <cmath>
#include <iostream>
#include <algorithm>
using namespace std;
const long long super_INF = 8000000000000000000;
const long long super_puper_INF = 8111111111111111111;
struct edge{
    int from = 0;
    int to = 0;
    long long weight = super_INF;
};

vector <edge> edges;
vector <vector <int>> graph;
vector <int> parent, ans;
vector <bool> used_1, used_2;
vector <long long> W_1, W_2;

void dfs(int v){
    ans.push_back(v);
    used_1[v] = true;
    int sizik = graph[v].size();
    for(int i = 0; i < sizik; ++i){
        int index = graph[v][i];
        if(!used_1[index]){
            dfs(index);
        }
    }
}

void dfs2(int v){
    ans.push_back(v);
    used_2[v] = true;
    int sizik = graph[v].size();
    for(int i = 0; i < sizik; ++i){
        int index = graph[v][i];
        if(!used_2[index]){
            dfs2(index);
        }
    }
}

int main(){
    int n, m, s;
    cin >> n >> m >> s;
    --s;
    edges.resize(m);
    graph.resize(n);
    used_1.resize(n, false);
    used_2.resize(n, false);
    parent.resize(n, -1);
    W_1.resize(n, super_puper_INF);
    W_2.resize(n);
    W_1[s] = 0;
    int from, to;
    long long weight;
    edge p;
    for(int i = 0; i < m; ++i){
        cin >> from >> to >> weight;
        --from;
        --to;
        p.from = from;
        p.to = to;
        p.weight = weight;
        edges[i] = p;
        graph[from].push_back(to);
    }
    //int t = -1;
    dfs(s);
    for(int j = 0; j < n - 1; ++j){
        for(int i = 0; i < m; ++i){
            from = edges[i].from;
            to = edges[i].to;
            weight = edges[i].weight;
            if (used_1[to] && (W_1[from] < super_INF) && (W_1[to] > W_1[from] + weight)) {
                W_1[to] = max(-super_INF, W_1[from] + weight);
            }
        }
    }
    W_2 = W_1;
    for(int i = 0; i < m; ++i){
        from = edges[i].from;
        to = edges[i].to;
        weight = edges[i].weight;
        if (used_1[to] && W_2[from] < super_INF && W_2[to] > W_2[from] + weight) {
            W_2[to] = max( -super_INF, W_2[from] + weight);
        }
    }
    for (int i = 0; i < n; ++i) {
        if (used_1[i] && W_2[i] != W_1[i]) {
            dfs2(i);
        }
    }
    for(int i = 0; i < n; ++i){
        if(W_1[i] >= super_INF){
            cout << "*" << endl;
            continue;
        }
        if(used_2[i]){
            cout << "-" << endl;
            continue;
        }
        cout << W_1[i] << endl;
    }
    return 0;
}