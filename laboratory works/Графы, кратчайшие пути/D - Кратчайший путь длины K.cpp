/*
Дан ориентированный граф. Найдите кратчайшие пути, состоящие из K рёбер, от S до всех вершин.

Входные данные
В первой строке дано целых четыре целых числа: 1 ≤ N, M ≤ 104 — количества вершин и рёбер, 0 ≤ K ≤ 100 — количество рёбер в кратчайших путях, 1 ≤ S ≤ N — начальная вершина.

В последующих M строках даны тройки целых чисел ai, bi, w — начало и конец ребра, а также его вес (1 ≤ ai, bi ≤ N,  - 105 ≤ w ≤ 105).

Выходные данные
Выведите ровно N чисел по одному в строке. i-е число — длина минимального пути из ровно K рёбер из S в i, или  - 1, если пути не существует.
*/

#include <fstream>
#include <vector>
#include <cmath>
#include <set>
#include <iostream>
using namespace std;
int n, m, k, s;

const int INF = 1000000000;

int main(){
    cin >> n >> m >> k >> s;
    --s;
    //vector<vector <int>> graph(n, vector<int>(n, INF));
    vector <pair <pair<int, int>, int>> E;
    int a, b, c;
    for(int i = 0; i < m; ++i){
        cin >> a >> b >> c;
        --a;
        --b;
        //graph[a][b] = c;
        E.push_back({{a, b}, c});
    }
    vector <vector <int>> d(k + 1, vector<int>(n, INF));
    d[0][s] = 0;
    int from, to, weight;
    for(int i = 1; i <= k; ++i){
        for(int j = 0; j < m; ++j){
            from = E[j].first.first;
            to = E[j].first.second;
            weight = E[j].second;
            if(d[i - 1][from] != INF){
                d[i][to] = min(d[i][to], d[i - 1][from] + weight);
            }
        }
    }
    for(int i = 0; i < n; ++i){
        if(d[k][i] == INF){
            cout << "-1" << endl;
            continue;
        }
        cout << d[k][i] << endl;
    }
    return 0;
}