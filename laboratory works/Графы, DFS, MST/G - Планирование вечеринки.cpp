/*
Петя планирует вечеринку, это дело непростое. 
Одна из главных проблем в том, что некоторые его друзья плохо ладят друг с другом, а некоторые — наоборот. 
В результате у него есть множество требований, например: «Я приду только если придет Гена» или «Если там будет Марина, то меня там точно не будет».

Петя формализовал все требования в следующем виде: «[+-]name1 => [+-]name2», здесь «name1» и «name2» — имена двух друзей Пети, 
«+» означает, что друг придет в гости, «-» — что не придет. 
Например, выражение «Если Андрея не будет, то Даша не придет» записывается так: «-andrey => -dasha».

Помогите Пете составить хоть какой-нибудь список гостей, удовлетворяющий всем свойствам, или скажите, что это невозможно

Входные данные
В первой строке входного файла записаны числа n и m — число друзей Пети и число условий (1 ≤ n, m ≤ 1000). 
В следующих n строках записаны имена друзей. Имена друзей состоят из маленьких латинских букв и имеют длину не больше 10. 
В следующих m строках записаны условия.

Выходные данные
Выведите в первой строке число k — число друзей, которых нужно пригласить. В следующих k строках выведите их имена.
*/

#include <vector>
#include <algorithm>
#include <iostream>
#include <cstring>

using namespace std;
int n, m, colour = 0;
string friends [10000];
vector <vector <int>> graph;
vector <vector <int>> trans_graph;
vector <bool> used;
vector <int> colours, top_sort;

void dfs_1 (int v) {
    used[v] = true;
    for (int i=0; i < graph[v].size(); ++i)
        if (!used[ graph[v][i] ])
            dfs_1 (graph[v][i]);
    top_sort.push_back (v);
}

void dfs_2 (int v) {
    colours[v] = colour;
    for (int i=0; i < trans_graph[v].size(); ++i)
        if (colours[trans_graph[v][i]] == -1)
            dfs_2 (trans_graph[v][i]);
}

void check(string a, string b){
    bool t1, t2;
    int ind_a = -1, ind_b = -1;
    a[0] == '+' ? t1 = true : t1 = false;
    b[0] == '+' ? t2 = true : t2 = false;
    a.erase(0, 1);
    b.erase(0, 1);
    for(int i = 0; i < n && (ind_a == -1 || ind_b == -1); i++){
        if(a == friends[i]){
            ind_a = i;
        }
        if(b == friends[i]){
            ind_b = i;
        }
    }
    if(t1){
        ind_a += n;
    }
    if(t2){
        ind_b += n;
    }
    graph[ind_a].push_back(ind_b);
    trans_graph[ind_b].push_back(ind_a);
    t1 ? (ind_a -= n) : (ind_a += n);
    t2 ? (ind_b -= n) : (ind_b += n);
    graph[ind_b].push_back(ind_a);
    trans_graph[ind_a].push_back(ind_b);
}

int main(){
    cin >> n >> m;
    for(int i = 0; i < n; i++){
        string s;
        cin >> s;
        friends[i] = s;
    }
    graph.resize(2*n);
    trans_graph.resize(2*n);
    used.resize(2*n);
    colours.resize(2*n);
    for(int i = 0; i < m; i++){
        string s1, s2;
        cin >> s1 >> s2 >> s2;
        check(s1, s2);
    }
    for(int i = 0; i < 2*n; i++){
        used[i] = false;
    }
    for(int i = 0; i < 2*n; i++){
        if(!used[i]){
            dfs_1(i);
        }
    }
    for(int i = 0; i < 2*n; i++){
        colours[i] = -1;
    }
    for(int i = 0; i < 2*n; i++){
        int u = top_sort[2*n - 1 - i];
        if(colours[u] == -1){
            colour++;
            dfs_2(u);
        }
    }
    vector <string> ans;
    for(int i = 0; i < n; i++){
        if(colours[i] < colours[i + n]){
            //cout << friends[i] << " " << colours[i] << " " << colours[i + n] << endl;
            ans.push_back(friends[i]);
        }
    }
    if(ans.empty()){
        cout << "-1";
    }
    else{
        cout << ans.size() << endl;
        for(int i = 0; i < ans.size(); i++){
            cout << ans[i] << endl;
        }
    }
    return 0;
}