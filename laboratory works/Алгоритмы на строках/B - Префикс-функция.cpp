/*
Постройте префикс-функцию для заданной строки s.

Входные данные
Первая строка входного файла содержит s (1 ≤ |s| ≤ 106). Строка состоит из букв латинского алфавита.

Выходные данные
Выведите значения префикс-функции строки s для всех индексов 1, 2, ..., |s|.
*/

#include <iostream>
#include <vector>
#include <set>
#include <algorithm>

using namespace std;


int main() {
    string s;
    cin >> s;
    int n = (int) s.length();
    vector<int> pi (n);
    for (int i=1; i<n; ++i) {
        int j = pi[i-1];
        while (j > 0 && s[i] != s[j])
            j = pi[j-1];
        if (s[i] == s[j])  ++j;
        pi[i] = j;
    }
    for(int i = 0; i < n; ++i){
        cout << pi[i] << " ";
    }
    return 0;
}