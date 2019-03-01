/*
Школьник Вася хочет найти запасы спрятанного кефира. По легенде, кефир находится в домиках a, b или c. Вася хочет проверить каждый из этих трёх домиков, потратив на это минимальное количество времени.

Местность, в которой находится Вася представляет собой n домиков, пронумерованных числами от 1 до n. Некоторые из домиков соединены дорогами, по которым можно ходить в обе стороны. Время прохождения i-й дороги составляет wi секунд. Путём в графе называется непустая последовательность вершин, такая что все соседние вершины соединены дорогой. Требуется помочь Васе найти путь, содержащий вершины a, b, c, такой что суммарное время прохождения всех дорог на пути минимально. При этом, если мы прошли по какой-то дороге дважды (или более), то и время её прохождения следует учитывать соответствующее количество раз. Начинать свой путь Вася может из любой вершины.

Гарантируется, что a, b, c — попарно различные домики.

Входные данные
В первой строке ввода записаны два числа n и m (3 ≤ n ≤ 100 000, 0 ≤ m ≤ 200 000) — количество домиков в ЛКШ и дорог между ними соответственно.

Следующие m строк содержат описания дорог, по одному в строке. Каждая из дорог задаётся тройкой чисел ui, vi, wi (1 ≤ ui, vi ≤ n, 1 ≤ wi ≤ 109) — номерами соединённых домиков и временем, затрачиваемым на прохождение данной дороги. По каждой дороге разрешено ходить в обе стороны. Гарантируется, что любая пара домиков соединена не болee чем одной дорогой. Также гарантируется, что нет дороги, соединяющей домик с самим собой.

В последней строке записаны три попарно различных числа a, b, c (1 ≤ a, b, c ≤ n).

Выходные данные
Выведите одно целое число — минимальное возможное время, которое нужно затратить на прохождение пути, содержащего домики a, b и c. Если пути, содержащего все три домика не существует, то выведите -1.
*/

#include <set>
#include <vector>
#include <cmath>
#include <iostream>
#include <algorithm>
using namespace std;

const long long NN = 1000000;

bool usedA[NN], usedB[NN], usedC[NN];
long long WA[NN], WB[NN], WC[NN];
vector <vector <pair <long long, long long>>> graph;
long long n, m;
const long long INF = 8000000000000000000ll;

void dfs(long long v, bool used[]){
    used[v] = true;
    long long sizik = graph[v].size();
    for(long long i = 0; i < sizik; ++i){
        long long index = graph[v][i].first;
        if(!used[index]){
            dfs(index, used);
        }
    }
}

void deikstra(long long ind, long long weights[], bool used[]){
    set <pair <long long, long long>> WEI;
    WEI.insert({0, ind});
    pair <long long, long long> v;
    for(int i = 0; i  < n; ++i){
        used[i] = !used[i];
    }
    while(!WEI.empty()){
        v = *(WEI.begin());
        WEI.erase(WEI.begin());
        if(used[v.second] || weights[v.second] < v.first){
            continue;
        }
        used[v.second] = true;
        long long index = v.second;
        for(int j = 0; j < graph[index].size(); ++j){
            long long ind = graph[index][j].first;
            long long weight = graph[index][j].second;
            if(!used[ind] && (weights[ind] > weight + weights[index])){
                weights[ind] = weight + weights[index];
                WEI.insert({weights[ind], ind});
            }
        }
    }
}

int main(){
    cin >> n >> m;
    for(long long i = 0; i < n; ++i){
        usedA[i] = false;
        usedB[i] = false;
        usedC[i] = false;
        WA[i] = INF;
        WB[i] = INF;
        WC[i] = INF;
    }
    graph.resize(n);
    long long u, v;
    long long w;
    for(long long i = 0; i < m; ++i){
        cin >> u >> v >> w;
        --u;
        --v;
        graph[u].push_back({v, w});
        graph[v].push_back({u, w});
    }
    long long a, b, c;
    cin >> a >> b >> c;
    --a;
    --b;
    --c;
    WA[a] = 0;
    WB[b] = 0;
    WC[c] = 0;
    dfs(a, usedA);
    dfs(b, usedB);
    dfs(c, usedC);
    if(!(usedA[b] && usedA[c] && usedB[a] && usedB[c] && usedC[a] && usedC[b])){
        cout << -1;
        return 0;
    }
    deikstra(a, WA, usedA);
    deikstra(b, WB, usedB);
    deikstra(c, WC, usedC);
    long long AB = WA[b];
    long long AC = WA[c];
    long long BA = WB[a];
    long long BC = WB[c];
    long long CA = WC[a];
    long long CB = WC[b];
    long long res[6] = {AB + BC, AC + CB, BA + AC, BC + CA, CA + AB, CB + BA};
    long long ans = INF;
    for(long long i = 0; i < 6; ++i){
        ans = min(ans, res[i]);
    }
    cout << ans;
    return 0;
}