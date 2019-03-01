#include <vector>
#include <iostream>
#include <sstream>
#include <cstdlib>

#include "bad_from_string.h"

template<class T>
T from_string(std::string &str) {
    std::istringstream inputString(str);
    inputString.exceptions(std::istringstream::failbit | std::istringstream::badbit);
    T t;
    try {
        inputString >> std::skipws >> t;
    }
    catch (std::istringstream::failure &f) {
        throw bad_from_string(f.what());
    }
    try {
        char c = 0;
        inputString >> c;
    }
    catch (std::istringstream::failure &f) {
        return t;
    }
    throw bad_from_string("Conversion error");
}

int main() {
    std::vector<std::pair<std::string, std::string>> stringQueries{{"aba", "aba"}, {"aba caba", "aba caba"}};
    std::vector<std::pair<std::string, std::string>> intQueries{{"10", "10"}, {"+10", "10"}, {"-10", "-10"}, {"0.1", "Error"}, {"1.000000e-02", "Error"}, {"0x1.47ae147ae147bp-7", "Error"}, {" 10", "Error"}, {"10 ", "Error"}, {" 10 ", "Error"}};
    std::vector<std::pair<std::string, std::string>> unsignedIntQueries{{"-10", "Error"}, {"", "Error"}, {"aba", "Error"}};
    std::vector<std::pair<std::string, std::string>> doubleQueries{{"10", "10"}, {"+10", "10"}, {"-10", "-10"}, {"0.01", "0.01"}, {"1.000000e-02", "0.01"}, {"0x1.47ae147ae147bp-7", "0.01"}, {" 10", "Error"}, {"10 ", "Error"}, {" 10 ", "Error"}, {"aba", "Error"}};

    for (auto &query : stringQueries) {
        std::cout << std::endl << "from_string(\"" << query.first << "\"):";
        std::cout << std::endl << "Excepted : " << query.second;
        try {
            std::cout << std::endl << "string: ";
            std::cout << from_string<std::string>(query.first);
        } catch (std::exception const &e) {
            std::cout << "exception: " << e.what();
        } catch (...) {
            std::cout << "catch unknown";
        }
        std::cout << std::endl;
    }

    for (auto &query : intQueries) {
        std::cout << std::endl << "from_string(\"" << query.first << "\"):";
        std::cout << std::endl << "Excepted : " << query.second;
        try {
            std::cout << std::endl << "int: ";
            std::cout << from_string<int>(query.first);
        } catch (std::exception const &e) {
            std::cout << "exception: " << e.what();
        } catch (...) {
            std::cout << "catch unknown";
        }
        std::cout << std::endl;
    }

    for (auto &query : unsignedIntQueries) {
        std::cout << std::endl << "from_string(\"" << query.first << "\"):";
        std::cout << std::endl << "Excepted : " << query.second;
        try {
            std::cout << std::endl << "unsigned int: ";
            std::cout << from_string<unsigned int>(query.first);
        } catch (std::exception const &e) {
            std::cout << "exception: " << e.what();
        } catch (...) {
            std::cout << "catch unknown";
        }
        std::cout << std::endl;
    }

    for (auto &query : doubleQueries) {
        std::cout << std::endl << "from_string(\"" << query.first << "\"):";
        std::cout << std::endl << "Excepted : " << query.second;
        try {
            std::cout << std::endl << "double: ";
            std::cout << from_string<double >(query.first);
        } catch (std::exception const &e) {
            std::cout << "exception: " << e.what();
        } catch (...) {
            std::cout << "catch unknown";
        }
        std::cout << std::endl;
    }
    return 0;
}