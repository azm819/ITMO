/*
Вычислите количество различных подстрок строки s.

Входные данные
Единственная строка входного файла содержит строку s (1 ≤ |s| ≤ 400 000). Строка состоит из строчных латинских букв.

Выходные данные
Выведите одно число — ответ на задачу.
*/

#include <fstream>
#include <vector>
#include <string>

using namespace std;

ifstream fin("count.in");
ofstream fout("count.out");
const int kAlphabetLength = 27;
const char kFirstChar = 'a' - 1;

class SuffixArray {
public:
    void ToSuffixArray(const string &new_str, vector<int> &answer);

private:
    void sort(int len);

    void sort_by_classes();

    string str;
    vector<int> sorted_array;
    vector<int> old_class;
    vector<int> new_class;
};

void SuffixArray::sort_by_classes() {
    vector<int> tmp(sorted_array.size());
    vector<int> class_count(sorted_array.size());
    for (int i = 0; i < class_count.size(); i++) {
        class_count[old_class[i]]++;
        tmp[i] = sorted_array[i];
    }
    int tmp_count = class_count[0];
    int prev_count = 0;
    class_count[0] = 0;
    for (int i = 1; i < class_count.size(); i++) {
        prev_count = tmp_count;
        tmp_count = class_count[i];
        class_count[i] = class_count[i - 1] + prev_count;
    }
    for (int i = 0; i < sorted_array.size(); i++) {
        sorted_array[class_count[old_class[tmp[i]]]++] = tmp[i];
    }
}

void SuffixArray::sort(int len) {
    old_class = new_class;
    for (int &i : sorted_array) {
        i = (sorted_array.size() + i - len) % sorted_array.size();
    }
    sort_by_classes();
    int class_number = 0;
    int first = 0;
    int second = 0;
    new_class[sorted_array[0]] = 0;
    for (int i = 1; i < str.size(); i++) {
        first = (sorted_array[i] + len) % sorted_array.size();
        second = (sorted_array[i - 1] + len) % sorted_array.size();
        if (old_class[sorted_array[i - 1]] != old_class[sorted_array[i]]
            || old_class[first] != old_class[second]) {
            class_number++;
        }
        new_class[sorted_array[i]] = class_number;
    }
}

void CountingSort(const string &str, vector<int> &sorted_array) {
    vector<int> count(kAlphabetLength);
    for (char curr_char : str) {
        count[curr_char - kFirstChar]++;
    }
    for (int i = 1; i < count.size(); i++) {
        count[i] += count[i - 1];
    }
    for (int i = 0; i < str.size(); i++) {
        sorted_array[--count[str[i] - kFirstChar]] = i;
    }
}

void SuffixArray::ToSuffixArray(const string &new_str, vector<int> &answer) {
    str = new_str;
    sorted_array.resize(str.size());
    old_class.resize(str.size());
    new_class.resize(str.size());
    CountingSort(str, sorted_array);
    int class_number = 0;
    for (int i = 1; i < str.size(); i++) {
        if (str[sorted_array[i - 1]] != str[sorted_array[i]]) {
            class_number++;
        }
        new_class[sorted_array[i]] = class_number;
    }
    for (int len = 1; len <= str.size(); len *= 2) {
        sort(len);
    }
    answer = sorted_array;
    sorted_array.clear();
    old_class.clear();
    new_class.clear();
}

void LCP(const string &str, vector<long long> &lcp) {
    lcp.resize(str.size());
    SuffixArray suff;
    vector<int> suff_array;
    suff.ToSuffixArray(str, suff_array);
    vector<int> suff_pos(suff_array.size());
    for (int i = 0; i < suff_array.size(); i++) {
        suff_pos[suff_array[i]] = i;
    }

    int max_prefix = 0;
    int second_pos = 0;
    for (int i = 0; i < str.size(); i++) {
        if (max_prefix > 0) {
            max_prefix--;
        }
        second_pos = suff_pos[i] + 1;
        if (second_pos >= suff_array.size()) {
            lcp[i] = 0;
            max_prefix = 0;
            continue;
        }
        int max_value = i > suff_array[second_pos] ? i : suff_array[second_pos];
        max_value += max_prefix;
        while (max_value < str.size()) {
            if (str[i + max_prefix] != str[suff_array[second_pos] + max_prefix]) {
                break;
            }
            max_prefix++;
            max_value = i > suff_array[second_pos] ? i : suff_array[second_pos];
            max_value += max_prefix;
        }
        lcp[i] = max_prefix;
    }
}

long long UniqueSubstringCount(const string &str) {
    vector<long long> lcp_array;
    LCP(str, lcp_array);
    long long count = 0;
    for (int i = 0; i < str.size(); i++) {
        count += str.size() - i - lcp_array[i];
    }
    return count - str.size();
}

int main() {
    string str;
    fin >> str;
    fout << UniqueSubstringCount(str + kFirstChar);
    vector <int> vec(str.length());
    for(int i = 0; i < str.length(); ++i){
        vec[i] = 1 << i;
    }
    return 0;
}