/*
Даны строки p и t. Требуется найти все вхождения строки p в строку t в качестве подстроки.

Входные данные
Первая строка входного файла содержит p, вторая — t (1 ≤ |p|, |t| ≤ 106). Строки состоят из букв латинского алфавита.

Выходные данные
В первой строке выведите количество вхождений строки p в строку t. 
Во второй строке выведите в возрастающем порядке номера символов строки t, с которых начинаются вхождения p. 
Символы нумеруются с единицы.
*/

#include <iostream>
#include <vector>
#include <set>
#include <algorithm>

using namespace std;

void make_str(string &s, string &t, char *res){
    int sl = s.length();
    int tl = t.length();
    for (int i = 0; i < sl; ++i){
        res[i] = s[i];
    }
    res[sl] = '#';
    for(int i = sl + 1; i < sl + tl + 1; ++i){
        res[i] = t[i - sl - 1];
    }
}

int main() {
    string s1, s2;
    cin >> s1 >> s2;
    int sizik = s1.length();
    char *s = new char[sizik + s2.length() + 1];
    make_str(s1, s2, s);
    int n = s1.length() + s2.length() + 1;
    vector<int> pi (n);
    for (int i=1; i<n; ++i) {
        int j = pi[i-1];
        while (j > 0 && s[i] != s[j])
            j = pi[j-1];
        if (s[i] == s[j])  ++j;
        pi[i] = j;
    }
    vector <int> res;
    for (int i = s1.length() + 1; i < n; ++i){
        if(pi[i] == sizik && i - 2*sizik >= 0){
            res.push_back(i - 2 * sizik);
        }
    }
    cout << res.size() << endl;
    for(int i = 0; i < res.size(); ++i){
        cout << res[i] + 1 << " ";
    }
    return 0;
}