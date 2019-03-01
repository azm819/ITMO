/*
Постройте суффиксный массив для заданной строки s, для каждых двух соседних суффиксов найдите длину максимального общего префикса.

Входные данные
Первая строка входного файла содержит строку s (1 ≤ |s| ≤ 400 000). Строка состоит из строчных латинских букв.

Выходные данные
В первой строке выведите |s| различных чисел — номера первых символов суффиксов строки s так, чтобы соответствующие суффиксы были упорядочены в лексикографически возрастающем порядке. Во второй строке выведите |s| - 1 чисел — длины наибольших общих префиксов.
*/

#include <fstream>
#include <vector>
#include <string>

using namespace std;

ifstream fin("array.in");
ofstream fout("array.out");
const int alphabet = 27;
vector<int> MakeSA(string &str, vector<int> &pos) {
    vector<int> permutation(str.length(), 0);
    vector<int> classes(str.length(), 0);
    vector<int> cnt(alphabet, 0);

    for (int i = 0; i < str.length(); ++i) {
        ++cnt[str[i] - 96];
    }
    for (int i = 1; i < alphabet; ++i) {
        cnt[i] += cnt[i - 1];
    }
    for (int i = 0; i < str.length(); ++i) {
        permutation[--cnt[str[i] - 96]] = i;
    }

    int cls = 1;
    classes[permutation[0]] = 0;
    for (int i = 1; i < permutation.size(); ++i) {
        if (str[permutation[i - 1]] != str[permutation[i]]) {
            ++cls;
        }
        classes[permutation[i]] = cls - 1;
    }

    vector<int> pn(str.length(), 0);
    vector<int> cn(str.length(), 0);
    for (int k = 0; (1 << k) < str.length(); ++k) {
        for (int i = 0; i < permutation.size(); ++i) {
            pn[i] = permutation[i] - (1 << k);
            if (pn[i] < 0) {
                pn[i] += permutation.size();
            }
        }
        vector<int> counter(cls, 0);
        for (int i = 0; i < pn.size(); ++i) {
            ++counter[classes[pn[i]]];
        }
        for (int i = 1; i < counter.size(); ++i) {
            counter[i] += counter[i - 1];
        }
        for (int i = static_cast<int>( pn.size() - 1 ); i >= 0; --i) {
            permutation[--counter[classes[pn[i]]]] = pn[i];
        }

        cls = 1;
        cn[permutation[0]] = 0;
        for (int i = 1; i < permutation.size(); ++i) {
            int temp1 = (permutation[i] + (1 << k)) % permutation.size();
            int temp2 = (permutation[i - 1] + (1 << k)) % permutation.size();
            if (classes[permutation[i]] != classes[permutation[i - 1]] || classes[temp1] != classes[temp2]) {
                ++cls;
            }
            cn[permutation[i]] = cls - 1;
        }

        for (int i = 0; i < classes.size(); ++i) {
            classes[i] = cn[i];
        }
    }

    vector<int> suffixArray(permutation.size());
    for (int i = 0; i < permutation.size(); ++i) {
        suffixArray[i] = permutation[i];
        pos[suffixArray[i]] = i;
    }

    return suffixArray;
}


vector<int> CountLCP(const string &str, const vector<int> &SA, const vector<int> &pos) {
    vector<int> lcp(str.length());
    int k = 0;
    for (int i = 0; i < str.length() - 1; ++i) {
        if (k > 0) {
            --k;
        }
        if (pos[i] == str.length() - 1) {
            lcp[str.length() - 1] = -1;
            k = 0;
        } else {
            int j = SA[pos[i] + 1];
            while (max(i + k, j + k) < str.length() && str[i + k] == str[j + k]) {
                ++k;
            }
            lcp[pos[i]] = k;
        }
    }
    return lcp;
}

int main() {
    string str;
    fin >> str;
    str += '`';
    vector<int> pos(str.length());
    vector<int> suffixArray = MakeSA(str, pos);
    vector<int> lcp = CountLCP(str, suffixArray, pos);
    for(int i = 1; i < str.length(); ++i){
        fout << suffixArray[i] + 1 << " ";
    }
    fout << endl;
    for (int i = 1; i < str.length() - 1; ++i) {
        fout << lcp[i] << " ";
    }
    vector <long long> vec(str.length());
    for(int i = 0; i < str.length(); ++i){
        vec[i] = 1 << i;
        vec[i] = 1 << vec[i];
    }
    return 0;
}