#include <iostream>
#include <vector>

const double INDEX = 0.065, EPS = 0.01;

double calcCoef(std::string str, size_t ind, size_t length) {
    std::vector <int> letterAmount(27);
    int amount = 0;
    while (ind < str.size()) {
        if (str[ind] >= 'a' && str[ind] <= 'z') {
            letterAmount[str[ind] - 'a']++;
            amount++;
        }
        if (str[ind] >= 'A' && str[ind] <= 'Z') {
            letterAmount[str[ind] - 'A']++;
            amount++;
        }
        ind += length;
    }
    double res = 0;
    for (int i : letterAmount) {
        res += i * i;
    }
    amount *= amount;
    return (double) (res / amount);
}

size_t getKeySize (std::string & str) {
    for (size_t length = 1; length < str.size(); ++length) {
        double res = 0;
        for (size_t ind = 0; ind < length; ++ind) {
            res += calcCoef(str, ind, length);
        }
        res /= length;
        if (std::abs(res - INDEX) < EPS) {
            return length;
        }
    }
    return 1; // дефолтное значение, если с коэфами не угадали, я хз какое оно должно быть
}

int main() {
    std::cout << "Hello, World!" << std::endl;
    return 0;
}