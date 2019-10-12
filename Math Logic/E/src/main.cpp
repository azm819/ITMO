//#include <iostream>
#include <fstream>
#include <vector>
#include <tuple>
#include <algorithm>
#include <map>
#include <set>
#include "expression.h"

// изменил парсер, т.к. не читало (A->A->A)->P(a). возможно, зря
// стоит убрать глубину, которая использовалась для сравнения

int index = 0;

expression *qual;
expression *newExpr;

bool equal(expression *first, expression *second) {
    if (first->getType() != second->getType())
        return false;
    char type = first->getType();
    if (type == '0') return true;
    if (type == 'v') {
        return first->getName() == second->getName();
    }
    if (type == 'f' || type == 'F') {
        auto fir = first->getIndex();
        auto sec = second->getIndex();
        if (allTerms[fir].size() != allTerms[sec].size()) return false;
        for (int i = 0; i < allTerms[fir].size(); ++i) {
            if (!equal(allTerms[fir][i], allTerms[sec][i])) return false;
        }
        return equal(first->getRight(), second->getRight());
    }
    if (type == '1' || type == 'n') {
        return equal(first->getRight(), second->getRight());
    }
    return equal(first->getLeft(), second->getLeft()) && equal(first->getRight(), second->getRight());
}

void checkFree(expression *expr, std::vector<std::string> &vars, std::vector<std::string> linkedVars) {
    char type = expr->getType();
    if (type == '?' || type == '@') {
        linkedVars.push_back(expr->getLeft()->getName());
        checkFree(expr->getRight(), vars, linkedVars);
        return;
    }
    if (type == '0') return;
    if (type == 'v') {
        if (find(linkedVars.begin(), linkedVars.end(), expr->getName()) == linkedVars.end()) {
            vars.push_back(expr->getName());
        }
        return;
    }
    if (type == 'f' || type == 'F') {
        int ind = expr->getIndex();
        for (auto &i : allTerms[ind]) {
            checkFree(i, vars, linkedVars);
        }
        return;
    }
    if (type == '1' || type == 'n') {
        checkFree(expr->getRight(), vars, linkedVars);
        return;
    }
    checkFree(expr->getLeft(), vars, linkedVars);
    checkFree(expr->getRight(), vars, linkedVars);
}

bool checkEquality(expression *first, expression *second, std::string &var, std::vector<std::string> &vars,
                   std::vector<std::string> linkedVars) {
    if (first->getType() == 'v'){
        if (first->getName() == var &&
            find(linkedVars.begin(), linkedVars.end(), first->getName()) == linkedVars.end()) {
            if (equal(newExpr, qual)) {
                newExpr = second;
                std::vector<std::string> vec1;
                checkFree(second, vars, vec1);
                for (const auto &temp : vars) {
                    if (find(linkedVars.begin(), linkedVars.end(), temp) != linkedVars.end()) {
                        return false;
                    }
                }
                return true;
            } else {
                if (equal(newExpr, second)) {
                    for (const auto &temp : vars) {
                        if (find(linkedVars.begin(), linkedVars.end(), temp) != linkedVars.end()) {
                            return false;
                        }
                    }
                    return true;
                } else {
                    return false;
                }
            }
        } else {
            return first->getName() == second->getName();
        }
    }
    if (first->getType() != second->getType()) {
        return false;
    }
    char type = first->getType();
    if (type == '?' || type == '@') {
        linkedVars.push_back(first->getLeft()->getName());
        return checkEquality(first->getRight(), second->getRight(), var, vars, linkedVars);
    }
    if (type == '0') return true;

    if (type == 'f' || type == 'F') {
        auto fir = first->getIndex();
        auto sec = second->getIndex();
        if (allTerms[fir].size() != allTerms[sec].size()) return false;
        for (int i = 0; i < allTerms[fir].size(); ++i) {
            if (!checkEquality(allTerms[fir][i], allTerms[sec][i], var, vars, linkedVars)) {
                return false;
            }
        }
        return checkEquality(first->getRight(), second->getRight(), var, vars, linkedVars);
    }
    if (type == '1' || type == 'n') {
        return checkEquality(first->getRight(), second->getRight(), var, vars, linkedVars);
    }
    return checkEquality(first->getLeft(), second->getLeft(), var, vars, linkedVars) &&
           checkEquality(first->getRight(), second->getRight(), var, vars, linkedVars);
}

int check(expression *expr) {
    if (expr->getType() == 'n' &&
        expr->getRight()->getType() == 'p' &&
        expr->getRight()->getLeft()->getType() == '1' &&
        expr->getRight()->getRight()->getType() == '0') {
        return 24;
    }
    if (expr->getType() == 'p') {
        expression *left = expr->getLeft();
        expression *right = expr->getRight();
        switch (left->getType()) {
            case 't':
                if (left->getRight()->getType() == '1' &&
                    right->getType() == '1' &&
                    right->getRight()->getType() == 't' &&
                    equal(left->getLeft(), right->getRight()->getLeft()) &&
                    equal(left->getRight()->getRight(), right->getRight()->getRight())) {
                    return 25;
                }
                if (left->getRight()->getType() == '0' &&
                    equal(left->getLeft(), right)) {
                    return 26;
                }
                break;
            case 'S':
                if (left->getRight()->getType() == '0' &&
                    right->getType() == '0') {
                    return 27;
                }
                if (left->getRight()->getType() == '1' &&
                    right->getType() == 't' &&
                    right->getLeft()->getType() == 'S' &&
                    equal(left->getLeft(), right->getRight()) &&
                    equal(left->getLeft(), right->getLeft()->getLeft()) &&
                    equal(left->getRight()->getRight(), right->getLeft()->getRight())) {
                    return 28;
                }
                break;
        }
    }
    if (expr->getType() != 'i') return 0;
    expression *left = expr->getLeft();
    expression *right = expr->getRight();
    switch (right->getType()) {
        case 'i': // 1, 3
            if (equal(left, right->getRight()))
                return 1;
            if (right->getRight()->getType() == 'c' &&
                equal(left, right->getRight()->getLeft()) &&
                equal(right->getLeft(), right->getRight()->getRight()))
                return 3;
            if (right->getLeft()->getType() == 'p' &&
                right->getRight()->getType() == 'p' &&
                left->getType() == 'p' &&
                equal(right->getLeft()->getRight(), right->getRight()->getRight()) &&
                equal(left->getLeft(), right->getLeft()->getLeft()) &&
                equal(left->getRight(), right->getRight()->getLeft())) {
                return 22;
            }
            break;
        case 'd': // 6, 7
            if (equal(left, right->getLeft()))
                return 6;
            if (equal(left, right->getRight()))
                return 7;
            break;
        case '?': { // 12
            auto tmp = right->getLeft()->getName();
            std::vector<std::string> vars, linkedVars;
            newExpr = qual;
            if (checkEquality(right->getRight(), left, tmp, vars, linkedVars)) {
                return 12;
            }
            break;
        }
        case 'p':
            if (right->getRight()->getType() == '1' &&
                right->getLeft()->getType() == '1' &&
                equal(right->getLeft()->getRight(), left->getLeft()) &&
                equal(right->getRight()->getRight(), left->getRight())) {
                return 21;
            }
            if (left->getRight()->getType() == '1' &&
                left->getLeft()->getType() == '1' &&
                equal(left->getLeft()->getRight(), right->getLeft()) &&
                equal(left->getRight()->getRight(), right->getRight())) {
                return 23;
            }
            break;
    }
    switch (left->getType()) {
        case 'i': { // 2, 8, 9
            if (right->getType() != 'i')
                break;
            if (right->getLeft()->getType() != 'i')
                break;
            expression *A = left->getLeft();
            expression *B = left->getRight();
            expression *leftUp = right->getLeft();
            expression *rightUp = right->getRight();
            switch (rightUp->getType()) {
                case 'i': // 2, 8
                    if (leftUp->getRight()->getType() == 'i' &&
                        equal(A, leftUp->getLeft()) &&
                        equal(A, rightUp->getLeft()) &&
                        equal(B, leftUp->getRight()->getLeft()) &&
                        equal(leftUp->getRight()->getRight(), rightUp->getRight()))
                        return 2;
                    if (rightUp->getLeft()->getType() == 'd' &&
                        equal(A, rightUp->getLeft()->getLeft()) &&
                        equal(B, leftUp->getRight()) &&
                        equal(B, rightUp->getRight()) &&
                        equal(leftUp->getLeft(), rightUp->getLeft()->getRight()))
                        return 8;
                    break;
                case 'n': // 9
                    if (leftUp->getRight()->getType() != 'n')
                        break;
                    if (equal(A, leftUp->getLeft()) &&
                        equal(A, rightUp->getRight()) &&
                        equal(B, leftUp->getRight()->getRight()))
                        return 9;
                    break;
            }
            break;
        }
        case 'c': // 4, 5
            if (equal(right, left->getLeft()))
                return 4;
            if (equal(right, left->getRight()))
                return 5;
            if (left->getRight()->getType() == '@' &&
                left->getRight()->getRight()->getType() == 'i' &&
                equal(right, left->getRight()->getRight()->getLeft())) {
                auto tmp = left->getRight()->getLeft()->getName();
                std::vector<std::string> vars, linkedVars;
                std::string newStr = "0";
                newExpr = new umno(new variable(newStr), '0');
                if (checkEquality(right, left->getLeft(), tmp, vars, linkedVars)) {
                    vars.clear();
                    linkedVars.clear();
                    newExpr = new umno(new variable(tmp), '1');
                    if (checkEquality(right, left->getRight()->getRight()->getRight(), tmp, vars, linkedVars)) {
                        return 29;
                    }
                }
            }
            break;
        case 'n': // 10
            if (left->getRight()->getType() == 'n')
                if (equal(left->getRight()->getRight(), right))
                    return 10;
            break;
        case '@': // 11
            // TODO
            auto tmp = left->getLeft()->getName();
            std::vector<std::string> vars, linkedVars;
            newExpr = qual;
            if (checkEquality(left->getRight(), right, tmp, vars, linkedVars)) {
                return 11;
            }
            break;
    }
    return 0;
}

expression *parse(std::string &str, size_t begin, size_t end);

expression *parseUn(std::string &str, size_t begin, size_t end);

expression *parseTerm(std::string &str, size_t begin, size_t end);

expression *combNeg(std::string &str, size_t begin, size_t end, int times) {
    if (times > 0) {
        return new negation(combNeg(str, begin + 1, end, times - 1));
    }
    return parseUn(str, begin, end);
}

int parseNeg(std::string &str, size_t begin, size_t end, size_t start) {
    if (str[start] == '!') {
        int res = parseNeg(str, begin, end, start + 1);
        if (res > 0)
            return res + 1;
        else
            return 0;
    }
    if (str[start] == '(') {
        int cnt = 1;
        int i = start + 1;
        while (cnt != 0) {
            if (str[i] == '(') cnt++;
            else if (str[i] == ')') cnt--;
            i++;
        }
        if (i == end)
            return 1;
        else return 0;
    } else {
        if (str[start] == '?' || str[start] == '@') {
            return 1;
        }
        bool isNeg = true;
        for (size_t i = start; i < end; ++i) {
            if (str[i] == '(') {
                int cnt = 1;
                int j = i + 1;
                while (cnt != 0) {
                    if (str[j] == '(') cnt++;
                    else if (str[j] == ')') cnt--;
                    j++;
                }
                i = j - 1;
            }
            if (str[i] == '-' || str[i] == '&' || str[i] == '|' || str[i] == '+' || str[i] == '*') {
                isNeg = false;
                break;
            }
        }
        if (isNeg) {
            return 1;
        } else {
            return 0;
        }
    }
}

expression *parseUmno(std::string &str, size_t begin, size_t end) {
    if (str[end - 1] == '\'') {
        return new umno(parseUmno(str, begin, end - 1), '1');
    } else if (end - begin == 1 && str[begin] == '0') {
        std::string newStr = "0";
        return new umno(new variable(newStr), '0');
    } else if (str[begin] >= 'a' && str[begin] <= 'z') {
        bool isVar = true;
        for (int i = begin; i < end; ++i) {
            if (str[i] == '(') {
                isVar = false;
                break;
            }
        }
        if (isVar) {
            std::string newStr = str.substr(begin, end - begin);
            return new variable(newStr);
        }
        size_t term_begin = begin;
        size_t term_end = end;
        for (size_t i = begin; i < end; ++i) {
            if (str[i] == '(') {
                term_begin = i;
                break;
            }
        }
        std::vector<expression *> terms;
        int ind = index++;
        allTerms.push_back(terms);
        size_t temp = term_begin + 1;
        for (size_t i = term_begin + 1; i < end; ++i) {
            if (str[i] == '(') {
                int cnt = 1;
                size_t j = i + 1;
                while (cnt != 0) {
                    if (str[j] == '(') cnt++;
                    else if (str[j] == ')') cnt--;
                    j++;
                }
                i = j - 1;
            } else if (str[i] == ',' || i == end - 1) {
                expression* exprrr = parseTerm(str, temp, i);
                allTerms[ind].push_back(exprrr);
                temp = i + 1;
            }
        }
        std::string newStr = str.substr(begin, term_begin - begin);
        return new umno(new variable(newStr), ind, 'F');
    } else if (str[begin] == '(') {
        int cnt = 1;
        size_t i = begin + 1;
        while (cnt != 0) {
            if (str[i] == '(') cnt++;
            else if (str[i] == ')') cnt--;
            i++;
        }
        if (i == end) {
            return parseTerm(str, begin + 1, end - 1);
        }
    }
    std::string newStr = str.substr(begin, end - begin);
    return new variable(newStr);
}

expression *parseSlag(std::string &str, size_t begin, size_t end) {
//    if (str[begin] == '(') {
//        int cnt = 1;
//        size_t i = begin + 1;
//        while (cnt != 0) {
//            if (str[i] == '(') cnt++;
//            else if (str[i] == ')') cnt--;
//            ++i;
//        }
//        if (i == end) {
//            return parseSlag(str, begin + 1, end - 1);
//        }
//    }
    for (size_t i = end - 1; i > begin; --i) {
        if (str[i] == ')') {
            int cnt = 1;
            size_t j = i - 1;
            while (cnt != 0 && j > begin) {
                if (str[j] == ')') cnt++;
                else if (str[j] == '(') cnt--;
                j--;
            }
            if (j == begin) break;
            i = j + 1;
        } else if (str[i] == '*') {
            return new slag(parseSlag(str, begin, i), parseUmno(str, i + 1, end));
        }
    }
    return parseUmno(str, begin, end);
}

expression *parseTerm(std::string &str, size_t begin, size_t end) {
    if (str[begin] == '(') {
        int cnt = 1;
        size_t i = begin + 1;
        while (cnt != 0) {
            if (str[i] == '(') cnt++;
            else if (str[i] == ')') cnt--;
            ++i;
        }
        if (i == end) {
            return parseTerm(str, begin + 1, end - 1);
        }
    }
    for (size_t i = end - 1; i > begin; --i) {
        if (str[i] == ')') {
            int cnt = 1;
            size_t j = i - 1;
            while (cnt != 0 && j > begin) {
                if (str[j] == ')') cnt++;
                else if (str[j] == '(') cnt--;
                j--;
            }
            if (j == begin) break;
            i = j + 1;
        } else if (str[i] == '+') {
            return new term(parseTerm(str, begin, i), parseSlag(str, i + 1, end));
        }
    }
    return parseSlag(str, begin, end);
}

expression *parseFun(std::string &str, size_t begin, size_t end) {
    if (str[begin] == '(') {
        int cnt = 1;
        size_t i = begin + 1;
        while (cnt != 0) {
            if (str[i] == '(') cnt++;
            else if (str[i] == ')') cnt--;
            ++i;
        }
        if (i == end) {
            return parseFun(str, begin + 1, end - 1);
        }
    }
    size_t term_begin = begin;
    size_t term_end = end;
    for (size_t i = begin; i < end; ++i) {
        if (str[i] == '(') {
            term_begin = i;
            break;
        }
    }
    if (term_begin == begin) {
        std::vector<expression *> terms;
        int ind = index++;
        allTerms.push_back(terms);
        std::string newStr = str.substr(begin, end - begin);
        return new function(new variable(newStr), ind);
    }
    std::vector<expression *> terms;
    int ind = index++;
    allTerms.push_back(terms);
    size_t temp = term_begin + 1;
    for (size_t i = term_begin + 1; i < end; ++i) {
        if (str[i] == '(') {
            int cnt = 1;
            size_t j = i + 1;
            while (cnt != 0) {
                if (str[j] == '(') cnt++;
                else if (str[j] == ')') cnt--;
                j++;
            }
            i = j - 1;
        } else if (str[i] == ',' || i == end - 1) {
            expression* exprr = parseTerm(str, temp, i);
            allTerms[ind].push_back(exprr);
            temp = i + 1;
        }
    }
    std::string newStr = str.substr(begin, term_begin - begin - 1);
    return new function(new variable(newStr), ind);
}

expression *parsePred(std::string &str, size_t begin, size_t end) {
    if (str[begin] == '(') {
        int cnt = 1;
        size_t i = begin + 1;
        while (cnt != 0) {
            if (str[i] == '(') cnt++;
            else if (str[i] == ')') cnt--;
            ++i;
        }
        if (i == end) {
            return parsePred(str, begin + 1, end - 1);
        }
    }
    if (str[begin] >= 'A' && str[begin] <= 'Z') {
        int i = begin;
        while (i < end && ((str[i] >= 'A' && str[i] <= 'Z') || (str[i] >= '0' && str[i] <= '9'))) {
            ++i;
        }
        if (i == end || str[i] == '(') {
            return parseFun(str, begin, end);
        } else {
            return parse(str, begin, end);
        }
    }
        for (size_t i = begin; i < end; ++i) {
            if (str[i] == '(') {
                int cnt = 1;
                size_t j = i + 1;
                while (cnt != 0) {
                    if (str[j] == '(') cnt++;
                    else if (str[j] == ')') cnt--;
                    j++;
                }
                i = j - 1;
            } else if (str[i] == '=') {
                return new predicat(parseTerm(str, begin, i), parseTerm(str, i + 1, end));
            }
        }
    std::string newStr = str.substr(begin, end - begin);
    return new variable(newStr);
}

expression *parseUn(std::string &str, size_t begin, size_t end) {
    if (str[begin] == '(') {
        int cnt = 1;
        size_t i = begin + 1;
        while (cnt != 0) {
            if (str[i] == '(') cnt++;
            else if (str[i] == ')') cnt--;
            ++i;
        }
        if (i == end) {
            return parse(str, begin + 1, end - 1);
        }
    }
    if (str[begin] == '!') {
        int res = parseNeg(str, begin, end, begin + 1);
        if (res > 0) {
            return combNeg(str, begin, end, res);
        }
    }
    if (str[begin] == '?' || str[begin] == '@') {
        for (size_t i = begin + 1; i < end; ++i) {
            if (str[i] == '.') {
                std::string newStr = str.substr(begin + 1, i - begin - 1);
                return new unary(new variable(newStr), parse(str, i + 1, end), str[begin]);
            }
        }
    }
    return parsePred(str, begin, end);
}

expression *parseCon(std::string &str, size_t begin, size_t end) {
//    if (str[begin] == '(') {
//        int cnt = 1;
//        size_t i = begin + 1;
//        while (cnt != 0) {
//            if (str[i] == '(') cnt++;
//            else if (str[i] == ')') cnt--;
//            ++i;
//        }
//        if (i == end) {
//            return parseCon(str, begin + 1, end - 1);
//        }
//    }
    for (size_t i = end - 1; i > begin; --i) {
        if (str[i] == ')') {
            int cnt = 1;
            size_t j = i - 1;
            while (cnt != 0 && j > begin) {
                if (str[j] == ')') cnt++;
                else if (str[j] == '(') cnt--;
                j--;
            }
            if (j == begin) break;
            i = j + 1;
        } else if (str[i] == '&') {
//            std::cout << str.substr(begin, i - begin) << " Con " << str.substr(i + 1, end - i - 1) << '\n';
            return new conjunction(parseCon(str, begin, i), parseUn(str, i + 1, end));
        }
    }
    return parseUn(str, begin, end);
}

expression *parseDis(std::string &str, size_t begin, size_t end) {
//    if (str[begin] == '(') {
//        int cnt = 1;
//        size_t i = begin + 1;
//        while (cnt != 0) {
//            if (str[i] == '(') cnt++;
//            else if (str[i] == ')') cnt--;
//            ++i;
//        }
//        if (i == end) {
//            return parseDis(str, begin + 1, end - 1);
//        }
//    }
    for (size_t i = end - 1; i > begin; --i) {
        if (str[i] == ')') {
            int cnt = 1;
            size_t j = i - 1;
            while (cnt != 0 && j > begin) {
                if (str[j] == ')') cnt++;
                else if (str[j] == '(') cnt--;
                j--;
            }
            if (j == begin) break;
            i = j + 1;
        } else if (str[i] == '|') {
            return new disjunction(parseDis(str, begin, i), parseCon(str, i + 1, end));
        }
    }
    return parseCon(str, begin, end);
}

expression *parseImp(std::string &str, size_t begin, size_t end, size_t start) {
//    std::cout << str.substr(begin, start - 2 - begin) << " Impl " << str.substr(start, end - start) << '\n';
//    std::cout << start << '\n';
    return new implication(parseDis(str, begin, start - 2), parse(str, start, end));
}

expression *parse(std::string &str, size_t begin, size_t end) {
    if (str[begin] == '(') {
        int cnt = 1;
        size_t i = begin + 1;
        while (cnt != 0) {
            if (str[i] == '(') cnt++;
            else if (str[i] == ')') cnt--;
            ++i;
        }
        if (i == end) {
            return parse(str, begin + 1, end - 1);
        }
    }
    for (size_t i = begin; i < end; ++i) {
        if (str[i] == '(') {
            int cnt = 1;
            size_t j = i + 1;
            while (cnt != 0) {
                if (str[j] == '(') cnt++;
                else if (str[j] == ')') cnt--;
                j++;
            }
            i = j - 1;
        } else if (str[i] == '-' && str[i + 1] == '>') {
            return parseImp(str, begin, end, i + 2);
        }
    }
    return parseDis(str, begin, end);
}

std::vector<expression *> doc;
std::vector<std::pair<int, int>> axioms;
std::vector<expression *> hypothesis;
std::map<std::string, std::vector<int>> ModusPonis;
std::set<int> Answer;


void solve(int ind) {
    Answer.insert(ind);
    if (axioms[ind].first == -1 || axioms[ind].first == -2) {
        return;
    }
    solve(axioms[ind].second);
    solve(axioms[ind].first);
}


const int INF = 1000000000;

std::vector<long long> depth;

std::vector<std::string> hypopotamus;

std::map<std::string, int> docSec;

//void print(expression * expr) {
//    auto type = expr->getType();
//    using namespace std;
//    if (type == 'v') {
//        return;
//    }
//    if (type == '0') {
//        return;
//    }
//    cout << expr->getName() << ' ' << type << '\n';
//    if (type == '1' || type == 'n' || type == 'f' || type == 'F') {
//        print(expr->getRight());
//        return;
//    }
//    print(expr->getLeft());
//    print(expr->getRight());
//}

void deleteSpaces(std::string &str) {
    for (int i = 0; i < str.length(); ++i)
        if (str[i] == ' ') {
            str.erase(i, 1);
            i--;
        }
}

int main() {
//    std::ios_base::sync_with_stdio(false);
//    std::cin.tie(nullptr);
    std::ifstream fin;
    fin.open("in.txt");
    std::ofstream fout;
    fout.open("out.txt");
    std::string newStr = "X";
    qual = new variable(newStr);
    std::string express;
    expression *base = nullptr;
    expression *result = nullptr;
    std::string ResStr;
//    getline(std::cin, express);
    getline(fin, express);
    deleteSpaces(express);


    int in = 0;
    for (int i = 0; i < express.length(); ++i) {
        if (express[i] == '(') {
            int cnt = 1;
            size_t j = i + 1;
            while (cnt != 0) {
                if (express[j] == '(') cnt++;
                else if (express[j] == ')') cnt--;
                j++;
            }
            i = j - 1;
        }
        switch (express[i]) {
            case ',':
                hypopotamus.push_back(express.substr(in, i - in));
                result = parse(hypopotamus.back(), 0, hypopotamus.back().length());
                in = i + 1;
                hypothesis.push_back(result);
                break;
            case '|':
                if (express[i + 1] != '-')
                    break;
                if (i != 0) {
                    hypopotamus.push_back(express.substr(in, i - in));
                    result = parse(hypopotamus.back(), 0, hypopotamus.back().length());
                    hypothesis.push_back(result);
                }
                ResStr = express.substr(i + 2, express.size() - i - 1);
                base = parse(ResStr, 0, ResStr.length());
                i = express.length();
                break;
            default:
                break;
        }
    }
    int sizik = 0;
    int zizi = hypothesis.size();
    int lineNumber = 0;
//    while (getline(std::cin, express)) {
    while (getline(fin, express)) {
        lineNumber++;
        if (express.empty()) break;
        deleteSpaces(express);
        result = parse(express, 0, express.length());
        auto iter = docSec.find(result->getName());
        if (iter != docSec.end()) continue;
        std::pair<int, int> ind = {-100, -100};
        for (int i = 0; i < zizi; ++i) {
            if (equal(hypothesis[i], result)) {
                ind = {-2, (i + 1)};
                break;
            }
        }
        long long death = INF;
        if (ind.first == -100) {
            ind = {-1, check(result)};
            if (ind.second == 0) {
                ind.first = -100;
                if (result->getType() == 'i') {
                    auto right = result->getRight();
                    auto left = result->getLeft();
                    if (result->getRight()->getType() == '@') {
                        auto tmp = right->getLeft()->getName();
                        std::vector<std::string> vars, linkedVars;
                        checkFree(left, vars, linkedVars);
                        if (find(vars.begin(), vars.end(), tmp) == vars.end()) {
                            for (auto &i : doc) {
                                if (i->getType() == 'i' &&
                                    equal(i->getLeft(), left) &&
                                    equal(i->getRight(), right->getRight())) {
                                    ind.first = 22;
                                    break;
                                }
                            }
                        }
                    }
                    if (ind.first == -100 && result->getLeft()->getType() == '?') {
                        auto tmp = left->getLeft()->getName();
                        std::vector<std::string> vars, linkedVars;
                        checkFree(right, vars, linkedVars);
                        if (find(vars.begin(), vars.end(), tmp) == vars.end()) {
                            for (auto &i : doc) {
                                if (i->getType() == 'i' &&
                                    equal(i->getLeft(), left->getRight()) &&
                                    equal(i->getRight(), right)) {
                                    ind.first = 33;
                                    break;
                                }
                            }
                        }
                    }
                }
                if (ind.first == -100) {
                    auto it = ModusPonis.find(result->getName());
                    if (it == ModusPonis.end()) {
//                        std::cout << "Line #" << lineNumber << " can't be obtained\n";
                        fout << "Line #" << lineNumber << " can't be obtained\n";
                        return 0;
                    } else {
                        for (auto &i: it->second) {
                            iter = docSec.find(doc[i]->getLeft()->getName());
                            if (iter != docSec.end() && (death > (depth[i] + depth[iter->second]))) {
                                ind = {i, iter->second};
                                death = depth[i] + depth[iter->second];
                            }
                        }
                    }
                }
            }
        }
        if (ind.first == -100) {
//            std::cout << "Line #" << lineNumber << " can't be obtained\n";
            fout << "Line #" << lineNumber << " can't be obtained\n";
            return 0;
        }
        if (death != INF) depth.push_back(death + 1);
        else depth.push_back(1);
        doc.push_back(result);
        axioms.push_back(ind);
        docSec[result->getName()] = sizik;
        ++sizik;
        if (result->getType() == 'i') {
            ResStr = result->getRight()->getName();
            auto key = ModusPonis.find(ResStr);
            if (key == ModusPonis.end()) {
                ModusPonis[ResStr] = {sizik - 1};
            } else {
                key->second.push_back(sizik - 1);
            }
        }
    }
    if (!equal(result, base)) {
//        std::cout << "Required hasn’t been proven\n";
        fout << "Required hasn’t been proven\n";
        return 0;
    }
//    std::cout << "Proof is correct\n";
    fout << "Proof is correct\n";
    return 0;
}