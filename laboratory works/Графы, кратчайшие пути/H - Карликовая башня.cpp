/*
Little Vasya is playing a new game named "Dwarf Tower". In this game there are n different items, which you can put on your dwarf character. Items are numbered from 1 to n. Vasya wants to get the item with number 1.

There are two ways to obtain an item:

You can buy an item. The i-th item costs ci money.
You can craft an item. This game supports only m types of crafting. To craft an item, you give two particular different items and get another one as a result.
Help Vasya to spend the least amount of money to get the item number 1.

Input
The first line of input contains two integers n and m (1 ≤ n ≤ 200 000;0 ≤ m ≤ 500 000) — the number of different items and the number of crafting types.

The second line contains n integers ci — values of the items (0 ≤ ci ≤ 109).

The following m lines describe crafting types, each line contains three distinct integers ai, xi, yi — ai is the item that can be crafted from items xi and yi (1 ≤ ai, xi, yi ≤ n; ai ≠ xi; xi ≠ yi; yi ≠ ai).

Output
The output should contain a single integer — the least amount of money to spend.
*/

#include <vector>
#include <cmath>
#include <stdio.h>
#include <set>
#include <fstream>
using namespace std;
int n, m;

ifstream fin ("dwarf.in");
ofstream fout ("dwarf.out");

vector <long long> weights;
vector <vector <pair <int, int>>> graph;


const long long INF = 10e10;

int main(){
    fin >> n >> m;
    weights.resize(n);
    graph.resize(n);
    set <pair <long long, int>> WEI;
    for(int i = 0; i < n; ++i){
        long long w;
        fin >> w;
        weights[i] = w;
        WEI.insert({w, i});
    }
    int a, x, y;
    bool t = true;
    for(int i = 0; i < m; i++){
        fin >> a >> x >> y;
        if(a == 1) t = false;
        --a;
        --x;
        --y;
        graph[x].push_back({a, y});
        graph[y].push_back({a, x});
    }
    if(t){
        fout << weights[0];
        return 0;
    }
    pair <long long, int> v;
    while(!WEI.empty()){
        v = *(WEI.begin());
        WEI.erase(WEI.begin());
        if(weights[v.second] < v.first){
            continue;
        }
        int index = v.second;
        for(int j = 0; j < graph[index].size(); ++j){
            int index1 = graph[index][j].first;
            int index2 = graph[index][j].second;
            if(weights[index1] > weights[index2] + weights[index]){
                weights[index1] = weights[index2] + weights[index];
                WEI.insert({weights[index1], index1});
            }
        }
    }
    fout << weights[0];
    return 0;
}