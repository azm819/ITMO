#include <iostream>
#include <tuple>
#include <typeinfo>

//9.1
template<typename T>
void print_values(T value) {
    std::cout << typeid(value).name() << " : " << value << std::endl;
}

template<typename T, typename... A>
void print_values(T value, A... args) {
    std::cout << typeid(value).name() << " : " << value << std::endl;
    print_values(args...);

}

//9.3
template<int i, int j, typename T>
auto to_pair(T &tup) -> decltype(std::make_pair(std::get<i>(tup), std::get<j>(tup))) {
    return std::make_pair(std::get<i>(tup), std::get<j>(tup));
}

int main() {
    print_values(0, 3.5, "Hello");
    auto t = std::make_tuple(0, 3.5, "Hello");
    std::pair<double, char const *> p = to_pair<1, 2>(t);
    std::cout << p.first << " " << p.second << std::endl;
    return 0;
}