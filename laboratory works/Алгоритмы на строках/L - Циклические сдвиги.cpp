/*
k-м циклическим сдвигом строки S называется строка, полученная перестановкой k первых символов строки S в конец строки.

Рассмотрим все различные циклические сдвиги строки S и отсортируем их по возрастанию. 
Требуется вычислить i-ю строчку этого массива.

Например, для строки abacabac существует четыре различных циклических сдвига: нулевой (abacabac), первый (bacabaca), второй (acabacab) и третий (cabacaba). 
После сортировки по возрастанию получится такой массив: abacabac, acabacab, bacabaca, cabacaba.

Входные данные
В первой строке входного файла записана строка S, длиной не более 100 000 символов с ASCII-кодами от 32 до 126. 
Во второй строке содержится единственное целое число k (1 ≤ k ≤ 100 000).

Выходные данные
В выходной файл выведите k-й по возрастанию циклический сдвиг строки S, или слово IMPOSSIBLE, если такого сдвига не существует.
*/

#include <fstream>
#include <vector>
#include <string>

using namespace std;

ifstream fin("shifts.in");
ofstream fout("shifts.out");
const int alphabet = 100;
pair <vector<int>, vector <int>> MakeSA(string &str, vector<int> &pos) {
    vector<int> permutation(str.length(), 0);
    vector<int> classes(str.length(), 0);
    vector<int> cnt(alphabet, 0);

    for (int i = 0; i < str.length(); ++i) {
        ++cnt[str[i] - 32];
    }
    for (int i = 1; i < alphabet; ++i) {
        cnt[i] += cnt[i - 1];
    }
    for (int i = 0; i < str.length(); ++i) {
        permutation[--cnt[str[i] - 32]] = i;
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

    return {suffixArray, cn};
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
    int n = str.length();
    vector<int> pos(str.length());
    pair <vector<int>, vector<int>> result = MakeSA(str, pos);
    str += str;
    int m;
    fin >> m;
    --m;
    for(int i = 0; i < n; ++i){
        if(result.second[result.first[i]] == m){
            for(int j = result.first[i]; j < result.first[i] + n; ++j){
                fout << str[j];
            }
            return 0;
        }
    }
    fout << "IMPOSSIBLE";
    return 0;
}