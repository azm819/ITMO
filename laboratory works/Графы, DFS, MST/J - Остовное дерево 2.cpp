/*
Требуется найти в связном графе остовное дерево минимального веса.

Входные данные
Первая строка входного файла содержит два натуральных числа n и m — количество вершин и ребер графа соответственно. 
Следующие m строк содержат описание ребер по одному на строке. 
Ребро номер i описывается тремя натуральными числами bi, ei и wi — номера концов ребра и его вес соответственно (1 ≤ bi, ei ≤ n, 0 ≤ wi ≤ 100 000). 
n ≤ 200 000, m ≤ 200 000.

Граф является связным.

Выходные данные
Первая строка выходного файла должна содержать одно натуральное число — вес минимального остовного дерева.
*/

#include <iostream>
#include <vector>
#include <algorithm>
#include <set>

using namespace std;

struct ribs{
int a = 0, b = 0, w = 0;
bool operator()(const ribs& ad, const ribs& bd) const
    {
        return ad.w < bd.w;
    }
};

int n, m;
vector <ribs> RIP;
vector <int> parent, size;

int find_set (int v) {
    if (v == parent[v])
        return v;
    parent[v] = find_set (parent[v]);
    return parent[v];
}

void union_sets (int a, int b) {
    a = find_set (a);
    b = find_set (b);
    if (a != b) {
        if (size[a] < size[b])
            swap (a, b);
        parent[b] = a;
        size[a] += size[b];
    }
}

int main(){
    cin >> n >> m;
    int a, b, c;
    RIP.resize(m);
    parent.resize(n + 1);
    size.resize(n + 1);
    for(int i = 0; i <= n; i++){
        parent[i] = i;
        size[i] = 1;
    }
    for(int i = 0; i < m; i++){
        cin >> a >> b >> c;
        if(a == b) continue;
        RIP[i].a = min(a, b);
        RIP[i].b = max(a, b);
        RIP[i].w = c;
    }
    long long ans = 0;
    sort(RIP.begin(), RIP.end(), ribs());
    for(int i = 0; i < RIP.size(); i++){
        a = find_set(RIP[i].a);
        b = find_set(RIP[i].b);
        if(a != b){
            union_sets(RIP[i].a, RIP[i].b);
            ans += RIP[i].w;
        }
    }
    cout << ans;
    return 0;
}