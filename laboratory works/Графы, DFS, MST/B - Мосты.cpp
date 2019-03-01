/*
Дан неориентированный граф, не обязательно связный, но не содержащий петель и кратных рёбер. Требуется найти все мосты в нём.

Входные данные
Первая строка входного файла содержит два натуральных числа n и m — количества вершин и рёбер графа соответственно (1 ≤ n ≤ 20 000, 1 ≤ m ≤ 200 000).

Следующие m строк содержат описание рёбер по одному на строке. 
Ребро номер i описывается двумя натуральными числами bi, ei — номерами концов ребра (1 ≤ bi, ei ≤ n).

Выходные данные
Первая строка выходного файла должна содержать одно натуральное число b — количество мостов в заданном графе. 
На следующей строке выведите b целых чисел — номера рёбер, которые являются мостами, в возрастающем порядке. 
Рёбра нумеруются с единицы в том порядке, в котором они заданы во входном файле.
*/

#include <iostream>
#include <vector>
#include <algorithm>
#include <iostream>
#include <cmath>

using namespace std;

struct rebr{
    int a = 0;
    int b = 0;
    bool c = true;
};

int n, m, timer = 0;
vector < vector <int>> graph;
vector <rebr> reb;
vector <bool> used;
vector <int> timein, fun;

bool dfs (int v, int parent) {
    used[v] = true;
    timein[v] = timer++;
    fun[v] = timein[v];
    for (int i=0; i < graph[v].size(); ++i) {
        int to = graph[v][i];
        if (to == parent)  continue;
        if (used[to])
            fun[v] = min (fun[v], timein[to]);
        else {
            dfs (to, v);
            fun[v] = min (fun[v], fun[to]);
        }
}
}

int main(){
    cin >> n >> m;
    int a, b;
    graph.resize(n + 1);
    used.resize(n+1);
    timein.resize(n+1);
    fun.resize(n+1);
    rebr p;
    for(int i = 0; i < m; i++){
        cin >> a >> b;
        p.a = min(a, b);
        p.b = max(a, b);
        reb.push_back(p);
        graph[a].push_back(b);
        graph[b].push_back(a);
    }
    for(int i = 0; i <= n; i++){
        used[i] = false;
    }
    for(int i = 1; i <= n; i++){
        if(!used[i]){
            dfs(i, -1);
        }
    }
    vector <int> ans;
    for(int i = 0; i < m; i++){
        if(fun[reb[i].a] > timein[reb[i].b] || fun[reb[i].b] > timein[reb[i].a]){
            ans.push_back(i + 1);
        }
    }
    cout << ans.size() << endl;
    for(int i = 0; i < ans.size(); i++){
        cout << ans[i] << endl;
    }
    return 0;
}
