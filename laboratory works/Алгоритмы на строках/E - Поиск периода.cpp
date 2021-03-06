/*
Дана строка s. Требуется найти минимальную по длине строку t, такую что s представима в виде конкатенации одной или нескольких строк t.

Входные данные
Первая строка входного файла содержит s (1 ≤ |s| ≤ 106). Строка состоит из букв латинского алфавита.

Выходные данные
Выведите длину искомой строки t.
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
    int left = 0;
    int right = 0;
    for (int i=1; i < n; ++i) {
        if (i <= right){
            pi[i] = min(right - i + 1, pi[i - left]);
        }
        while (pi[i] + i < n && s[pi[i]] == s[i + pi[i]]){
            ++pi[i];
        }
        if(i >= right - pi[i]){
            left = i;
            right = i + pi[i] - 1;
        }
    }
    for(int i = 1; i < n; ++i){
        if(i + pi[i] == n && n % i == 0){
            cout << i;
            return 0;
        }
    }
    cout << n;
    return 0;
}