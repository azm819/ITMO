/*
Дан ориентированный граф. Определите, есть ли в нем цикл отрицательного веса, и если да, то выведите его.

Входные данные
Во входном файле в первой строке число N (1 ≤ N ≤ 100) — количество вершин графа. 
В следующих N строках находится по N чисел — матрица смежности графа. Все веса ребер не превышают по модулю 10 000. 
Если ребра нет, то соответствующее число равно 100 000.

Выходные данные
В первой строке выходного файла выведите «YES», если цикл существует или «NO» в противном случае. 
При его наличии выведите во второй строке количество вершин в искомом цикле и в третьей строке — вершины входящие в этот цикл в порядке обхода.
*/

#include <fstream>
#include <vector>
#include <cmath>
#include <iostream>
#include <algorithm>
using namespace std;

struct edge{
    int from = 0;
    int to = 0;
    int weight = 0;
};

vector <edge> graph;
vector <int> W, parent;
const int INF = 100000;
const int super_INF = 1000000000;

int main(){
    int n;
    cin >> n;
    W.resize(n);
    parent.resize(n, -1);
    int a;
    edge p;
    for(int i = 0; i < n; ++i){
        for(int j = 0; j < n; j++){
            cin >> a;
            if(a != INF){
                p.from = i;
                p.to = j;
                p.weight = a;
                graph.push_back(p);
            }
        }
    }
    int t = -1;
    int sizik = graph.size();
    for(int j = 0; j < n; ++j){
        t = -1;
        for(int i = 0; i < sizik; ++i)
            if (W[graph[i].to] > W[graph[i].from] + graph[i].weight) {
                W[graph[i].to] = max(-super_INF, W[graph[i].from] + graph[i].weight);
                parent[graph[i].to] = graph[i].from;
                t = graph[i].to;
            }
    }

    if (t == -1){
        cout << "NO";
    }
    else{
        int x = t;
        for (int i = 0; i < n; ++i)
            x = parent[x];
        vector <int> cycle;
        for (int c = x; ; c = parent[c]) {
            if(c >= 0 && c < n) cycle.push_back(c);
            if (c < 0 || c >= n || (c == x && cycle.size() > 1)) break;

        }
        cout << "YES" << endl;
        cout << cycle.size() - 1 << endl;
        for (int i = cycle.size() - 2; i >= 0; --i)
            cout << cycle[i] + 1 << ' ';
    }
    return 0;
}