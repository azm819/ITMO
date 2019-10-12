#include <iostream>
#include <vector>

using namespace std;

int main() {
    int a, b;
    vector <int> res;
    cin >> a >> b;
    for (int i = 0; i < a*b; ++i) {
        int c = 0;
        cin >> c;
        res.push_back(c);
    }
    for (int i = 0; i < b; ++i) {
        for (int j = 0; j < a; ++j) {
            cout << res[i * a + j] << ", ";
        }
        cout << '\n';
    }
    return 0;
}