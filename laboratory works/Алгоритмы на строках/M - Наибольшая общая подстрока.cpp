/*
Найдите наибольшую общую подстроку строк s и t.

Входные данные
Первая строка входного файла содержит строку s, вторая — t (1 ≤ |s|, |t| ≤ 100, 000). 
Строки состоят из строчных латинских букв.

Выходные данные
Выведите одну строку — наибольшую общую подстроку строк s и t. 
В случае, если ответ не единственный, выведите минимальный лексикографически.
*/

#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include <cmath>
#include <set>

using namespace std;
ifstream fin ("common.in");
ofstream fout ("common.out");

string s, t;
int n, m;
const long long T = 17;
const long long R = static_cast<const long long int>(pow(2, 60));
vector <long long> powers;
vector <long long> hashesS, hashesT;
set <long long> hashes;
pair <int, int> ans;
long long getHashS(int i, int j){
    if(i == 0){
        return  hashesS[j];
    }
    long long res = (hashesS[j] - (hashesS[i - 1] * powers[j - i + 1]) % R) % R;
    return (res < 0 ? res + R : res);
}

long long getHashT(int i, int j){
    if(i == 0){
        return  hashesT[j];
    }
    long long res = (hashesT[j] - (hashesT[i - 1] * powers[j - i + 1]) % R) % R;
    return (res < 0 ? res + R : res);
}

bool predikat(int key){
    hashes.clear();
    for(int i = 0; i < n - key; ++i){
        hashes.insert(getHashS(i, i + key));
    }
    for(int i = 0; i < m - key; ++i){
        long long hash = getHashT(i, i + key);
        if(hashes.count(hash)){
            ans = {i, i + key};
            return true;
        }
    }
    return false;
}

int main() {
    fin >> s >> t;
    n = s.length();
    m = t.length();
    powers.resize((unsigned int) max(n, m));
    powers[0] = 1;
    for(int i = 1; i < max(n, m); ++i){
        powers[i] = (powers[i - 1] * T) % R;
        if(powers[i] < 0) powers[i] += R;
    }
    hashesS.resize(n);
    hashesS[0] = (s[0]) % R;
    for(int i = 1; i < n; ++i){
        hashesS[i] = (hashesS[i - 1] * T) % R;
        if(hashesS[i] < 0) hashesS[i] += R;
        hashesS[i] = (hashesS[i] + s[i]) % R;
        if(hashesS[i] < 0) hashesS[i] += R;
    }
    hashesT.resize(m);
    hashesT[0] = (t[0]) % R;
    for(int i = 1; i < m; ++i){
        hashesT[i] = (hashesT[i - 1] * T) % R;
        if(hashesT[i] < 0) hashesT[i] += R;
        hashesT[i] = (hashesT[i] + t[i]) % R;
        if(hashesT[i] < 0) hashesT[i] += R;
    }
    int l = -1;
    int r = min(n, m);
    while (l < r - 1){
        int m = (l + r) / 2;
        if(predikat(m)){
            l = m;
        } else{
            r = m;
        }
    }
    for(int i = ans.first; i <= ans.second; ++i){
        fout << t[i];
    }
    return 0;
}