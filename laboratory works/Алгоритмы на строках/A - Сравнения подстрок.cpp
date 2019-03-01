/*
Дана строка. Нужно уметь отвечать на запросы вида: равны ли подстроки [a..b] и [c..d].

Входные данные
Сперва строка S (не более 105 строчных латинских букв). Далее число M — количество запросов.

В следующих M строках запросы a,b,c,d. 0 ≤ M ≤ 105, 1 ≤ a ≤ b ≤ |S|, 1 ≤ c ≤ d ≤ |S|

Выходные данные
M строк. Выведите Yes, если подстроки совпадают, и No иначе.
*/

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <cmath>
using namespace std;
string s;
const long long t = 17;
const long long r = static_cast<const long long int>(pow(2, 60));
vector <long long> powers;
vector <long long> hashes;
long long getHash(int i, int j){
    if(i == 0){
        return  hashes[j];
    }
    long long res = (hashes[j] - (hashes[i - 1] * powers[j - i + 1]) % r) % r;
    return (res < 0 ? res + r : res);
}

int main() {
    cin >> s;
    int n = s.length();
    powers.resize(n);
    powers[0] = 1;
    for(int i = 1; i < n; ++i){
        powers[i] = (powers[i - 1] * t) % r;
        if(powers[i] < 0) powers[i] += r;
    }
    hashes.resize(n);
    hashes[0] = (s[0]) % r;
    for(int i = 1; i < n; ++i){
        hashes[i] = (hashes[i - 1] * t) % r;
        if(hashes[i] < 0) hashes[i] += r;
        hashes[i] = (hashes[i] + s[i]) % r;
        if(hashes[i] < 0) hashes[i] += r;
    }
    int m;
    cin >> m;
    int a, b, c, d;
    for(int i = 0; i < m; ++i){
        cin >> a >> b >> c >> d;
        if(b - a != d - c){
            cout << "No" << endl;
            continue;
        }
        if(a == c && b == d){
            cout << "Yes" << endl;
            continue;
        }
        if(a == b && c == d){
            cout << (s[a - 1] == s[c - 1] ? "Yes" : "No") << endl;
            continue;
        }
        --a;
        --b;
        --c;
        --d;
        cout << (s[a] == s[c] && s[b] == s[d] && s[(a + b) / 2] == s[(c + d) / 2] && getHash(a, b) == getHash(c, d) ? "Yes" : "No") << endl;
    }
    return 0;
}