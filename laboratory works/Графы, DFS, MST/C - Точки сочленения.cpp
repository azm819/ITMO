/*
Дан неориентированный граф. Требуется найти все точки сочленения в нём.

Входные данные
Первая строка входного файла содержит два натуральных числа n и m — количества вершин и рёбер графа соответственно (1 ≤ n ≤ 20 000, 1 ≤ m ≤ 200 000).

Следующие m строк содержат описание рёбер по одному на строке. 
Ребро номер i описывается двумя натуральными числами bi, ei — номерами концов ребра (1 ≤ bi, ei ≤ n).

Выходные данные
Первая строка выходного файла должна содержать одно натуральное число b — количество точек сочленения в заданном графе. 
На следующей строке выведите b целых чисел — номера вершин, которые являются точками сочленения, в возрастающем порядке.
*/

#include <iostream>
#include <vector>
#include <algorithm>
#include <iostream>
#include <cmath>

using namespace std;

int n, m, timer = 0;
vector < vector <int>> graph;
vector <bool> used, soch;
vector <int> timein, fun;

bool dfs (int v, int parent) {
    used[v] = true;
    timein[v] = timer++;
    fun[v] = timein[v];
    int ch = 0;
    for (int i = 0; i < graph[v].size(); ++i) {
        int to = graph[v][i];
        if (to == parent)  continue;
        if (used[to])
            fun[v] = min (fun[v], timein[to]);
        else {
            dfs (to, v);
            fun[v] = min (fun[v], fun[to]);
            if( fun[to] >= timein[v] && parent != -1){
                soch[v] = true;
            }
            ch++;
        }
    if( parent == -1 && ch > 1){
        soch[v] = true;
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
        graph[a].push_back(b);
        graph[b].push_back(a);
    }
    for(int i = 0; i <= n; i++){
        used[i] = false;
        soch[i] = false;
    }
    for(int i = 1; i <= n; i++){
        if(!used[i]){
            dfs(i, -1);
        }
    }
    vector <int> ans;
    for(int i = 1; i <= n; i++){
        if(soch[i]){
            ans.push_back(i);
        }
    }
    cout << ans.size() << endl;
    for(int i = 0; i < ans.size(); i++){
        cout << ans[i] << " ";
    }
    return 0;
}
