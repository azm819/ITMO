/*
Дан неориентированный связный взвешенный граф. Найдите кратчайшее расстояние от первой вершины до всех вершин.

Входные данные
В первой строке входного файла два числа: n и m (2 ≤ n ≤ 30000, 1 ≤ m ≤ 400000), где n — количество вершин графа, а m — количество ребер.

Следующие m строк содержат описание ребер. Каждое ребро задается стартовой вершиной, конечной вершиной и весом ребра. 
Вес каждого ребра — неотрицательное целое число, не превосходящее 104.

Выходные данные
Выведите n чисел — для каждой вершины кратчашее расстояние до нее.
*/

#include <fstream>
#include <vector>
#include <cmath>
#include <stdio.h>
#include <set>
#include <iostream>
using namespace std;
int n, m;

struct node{
    int index = 0;
    int w = 0;
};

vector <long long> weights;
vector <bool> used;
vector <vector <node>> graph;
const int INF = 100 * 400000 + 1;


int main(){/*
    set <pair <int, int>> WEI;
    pair <int, int> v;
    while(true){
        int a, b;
        cin >> a >> b;
        cout << endl;
        WEI.insert({a, b});
        for(auto i = WEI.begin(); i != WEI.end(); i++){
            v = *i;
            cout << v.first << " " << v.second << endl;
        }
        cout << endl;
    }*/
    scanf("%d %d",&n, &m);
    graph.resize(n);
    int a, b, c;
    node t;
    for(int i = 0; i < m; ++i){
        scanf("%d %d %d", &a, &b, &c);
        --a;
        --b;
        t.w = c;
        t.index = b;
        graph[a].push_back(t);
        t.index = a;
        graph[b].push_back(t);
    }
    weights.resize(n, INF);
    used.resize(n, false);
    weights[0] = 0;
    set <pair <long long, int>> WEI, WEI_1;
    WEI.insert({0, 0});
    pair <long long, int> v;
    for(int k = 0; k < n; ++k){
        v = *(WEI.begin());
        while(!WEI.empty() && (used[v.second] || weights[v.second] < v.first)){
            WEI.erase(WEI.begin());
            v = *(WEI.begin());
        }
        //if(WEI.empty() || v.first == INF || v.second == -1) break;
        used[v.second] = true;
        int index = v.second;
        for(int j = 0; j < graph[index].size(); ++j){
            int ind = graph[index][j].index;
            int weight = graph[index][j].w;
            if(!used[ind] && (weights[ind] > weight + weights[index])){
                weights[ind] = weight + weights[index];
                WEI.insert({weights[ind], ind});
            }
        }
    }
    for(int i = 0; i < n; ++i){
        printf("%d ", weights[i]);
    }
    return 0;
}