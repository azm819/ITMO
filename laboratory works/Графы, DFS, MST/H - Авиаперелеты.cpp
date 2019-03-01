/*
Главного конструктора Петю попросили разработать новую модель самолета для компании «Air Бубундия». 
Оказалось, что самая сложная часть заключается в подборе оптимального размера топливного бака.

Главный картограф «Air Бубундия» Вася составил подробную карту Бубундии. 
На этой карте он отметил расход топлива для перелета между каждой парой городов.

Петя хочет сделать размер бака минимально возможным, для которого самолет сможет долететь от любого города в любой другой (возможно, с дозаправками в пути).

Входные данные
Первая строка входного файла содержит натуральное число n (1 ≤ n ≤ 1000) — число городов в Бубундии.

Далее идут n строк по n чисел каждая. j-ое число в i-ой строке равно расходу топлива при перелете из i-ого города в j-ый. 
Все числа не меньше нуля и меньше 109. Гарантируется, что для любого i в i-ой строчке i-ое число равно нулю.

Выходные данные
Первая строка выходного файла должна содержать одно число — оптимальный размер бака.
*/

#include <vector>
#include <algorithm>
#include <fstream>

using namespace std;

int n, med = 0;
vector <vector<int>> graph, trans_graph;
vector <bool> used;
vector <int> top_sort;
vector <int> bibs;

void dfs_1 (int v) {
    used[v] = true;
    for (int i = 0; i < n; ++i)
        if (!used[i] && (graph[v][i] <= med))
            dfs_1(i);
    top_sort.push_back(v);
}

void dfs_2 (int v) {
    used[v] = true;
    for (int i = 0; i < n; ++i)
        if (!used[i] && (trans_graph[v][i] <= med))
            dfs_2(i);
}

bool check(){
    top_sort.clear();
    for(int i = 0; i < n; i++){
        used[i] = false;
    }
    for(int i = 1; i < n; i++){
        if(!used[i]){
            dfs_1(i);
        }
    }
    for(int i = 0; i < n; i++){
        used[i] = false;
    }
    int ch = 0;
    for(int i = 0; i < n; i++){
        int u = top_sort[n - 1 - i];
        if(!used[u]){
            ch++;
            dfs_2(u);
        }
    }
    if(ch > 1){
        return false;
    }
    return true;
}

int searchik(){
    if(bibs.size() > 0){
        int l = 0;
        int r = bibs.size() - 1;
        while(l < r - 1){
            int m = (l + r) / 2;
            med = bibs[m];
            if(check()){
                r = m;
            }else{
                l = m;
            }
        }
        return bibs[r];
    }
    else{
        return 0;
    }
}

int main(){
    ifstream fin;
    fin.open("avia.in");
    ofstream fout;
    fout.open("avia.out");
    fin >> n;
    int a;
    graph.resize(n);
    trans_graph.resize(n);
    used.resize(n);
    for(int i = 0; i < n; i++){
        graph[i].resize(n);
        trans_graph[i].resize(n);
    }
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            fin >> a;
            if(a) bibs.push_back(a);
            graph[i][j] = a;
            trans_graph[j][i] = a;
        }
    }
    sort(bibs.begin(), bibs.end());
    fout << searchik();
    return 0;
}