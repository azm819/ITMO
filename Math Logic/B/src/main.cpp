#include <iostream>
#include <vector>
#include <tuple>
#include <algorithm>
#include <map>
#include <set>
#include "expression.h"

bool equal(expression *first, expression *second) {
    if (first->getDepth() != second->getDepth() || first->getType() != second->getType())
        return false;
    switch (first->getType()) {
        case 'v':
            return first->getName() == second->getName();
        case 'n':
            return equal(first->getRight(), second->getRight());
        default:
            return equal(first->getRight(), second->getRight()) && equal(first->getLeft(), second->getLeft());
    }
}

int check(expression *expr) {
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
            break;
        case 'd': // 6, 7
            if (equal(left, right->getLeft()))
                return 6;
            if (equal(left, right->getRight()))
                return 7;
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
            break;
        case 'n': // 10
            if (left->getRight()->getType() == 'n')
                if (equal(left->getRight()->getRight(), right))
                    return 10;
            break;
    }
    return 0;
}

expression *parse(std::string &str, size_t begin, size_t end);

expression *combNeg(std::string &str, size_t begin, size_t end, int times) {
    if (times > 0) {
//        std::cout << "Neg: " << str.substr(begin + 1, end - 1 - begin) << '\n';
        return new negation(combNeg(str, begin + 1, end, times - 1));
    }
    return parse(str, begin, end);
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
        bool isNeg = true;
        for (size_t i = start; i < end; ++i) {
            if (str[i] == '&' || str[i] == '-' || str[i] == '|' || str[i] == '(') {
                isNeg = false;
                break;
            }
        }
        if (isNeg) return 1;
        else return 0;
    }
}

expression *parseImp(std::string &str, size_t begin, size_t end, size_t start) {
//    std::cout << str.substr(begin, start - 2 - begin) << " Impl " << str.substr(start, end - start) << '\n';
    return new implication(parse(str, begin, start - 2), parse(str, start, end));
}

expression *parseDis(std::string &str, size_t begin, size_t end, size_t start) {
    for (size_t i = start; i < end; ++i) {
        if (str[i] == '(') {
            int cnt = 1;
            size_t j = i + 1;
            while (cnt != 0) {
                if (str[j] == '(') cnt++;
                else if (str[j] == ')') cnt--;
                j++;
            }
            if (j == end && i == begin) {
                return parse(str, begin + 1, end - 1);
            }
            i = j - 1;
        } else if (str[i] == '|') {
            return parseDis(str, begin, end, i + 1);
        } else if (str[i] == '-' && str[i + 1] == '>') {
            return parseImp(str, begin, end, i + 2);
        }
    }
//    std::cout << str.substr(begin, start - begin) << " Dis " << str.substr(start, end - start) << '\n';
    return new disjunction(parse(str, begin, start - 1), parse(str, start, end));
}

expression *parseCon(std::string &str, size_t begin, size_t end, size_t start) {
    for (size_t i = start; i < end; ++i) {
        if (str[i] == '(') {
            int cnt = 1;
            size_t j = i + 1;
            while (cnt != 0) {
                if (str[j] == '(') cnt++;
                else if (str[j] == ')') cnt--;
                j++;
            }
            if (j == end && i == begin) {
                return parse(str, begin + 1, end - 1);
            }
            i = j - 1;
        } else if (str[i] == '&') {
            return parseCon(str, begin, end, i + 1);
        } else if (str[i] == '|') {
            return parseDis(str, begin, end, i + 1);
        } else if (str[i] == '-' && str[i + 1] == '>') {
            return parseImp(str, begin, end, i + 2);
        }
    }
//    std::cout << str.substr(begin, start - 1 - begin) << " Con " << str.substr(start, end - start) << '\n';
    return new conjunction(parse(str, begin, start - 1), parse(str, start, end));
}


expression *parse(std::string &str, size_t begin, size_t end) {
    if (str[begin] == '!') {
        int res = parseNeg(str, begin, end, begin + 1);
        if (res > 0) {
            return combNeg(str, begin, end, res);
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
            if (j == end && i == begin) {
                return parse(str, begin + 1, end - 1);
            }
            i = j - 1;
        } else if (str[i] == '&') {
            return parseCon(str, begin, end, i + 1);
        } else if (str[i] == '|') {
            return parseDis(str, begin, end, i + 1);
        } else if (str[i] == '-' && str[i + 1] == '>') {
            return parseImp(str, begin, end, i + 2);
        }
    }
//    std::cout << "Var: " << str.substr(begin, end - begin) << '\n';
    std::string newStr = str.substr(begin, end - begin);
    return new variable(newStr);
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

void deleteSpaces(std::string &str) {
    for (int i = 0; i < str.length(); ++i)
        if (str[i] == ' ') {
            str.erase(i, 1);
            i--;
        }
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::string express;
    expression *base = nullptr;
    expression *result = nullptr;
    std::string ResStr;

//    while (getline(std::cin, express)) {
//        if (express.empty()) break;
//        deleteSpaces(express);
//        base = parse(express, 0, express.length());
//        std::cout << "Name: " << base->getName() << '\n';
//        std::cout << "Type: " << base->getType() << '\n';
//        std::cout << check(base) << '\n';
//    }


    getline(std::cin, express);
    deleteSpaces(express);


    int in = 0;
    for (int i = 0; i < express.length(); ++i) {
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
    while (getline(std::cin, express)) {
//        if (express.empty()) break;
        deleteSpaces(express);
        result = parse(express, 0, express.length());
        auto iter = docSec.find(result->getName());
        if (iter != docSec.end()) continue;
        std::pair<int, int> ind = {-100, -100};
        for (int i = 0; i < zizi; ++i)
            if (equal(hypothesis[i], result)) {
                ind = {-2, (i + 1)};
                break;
            }
        long long death = INF;
        if (ind.first == -100) {
            ind = {-1, check(result)};
            if (ind.second == 0) {
                ind.first = -100;
                auto it = ModusPonis.find(result->getName());
                if (it == ModusPonis.end()) {
                    std::cout << "Proof is incorrect";
                    return 0;
                } else {
                    for (auto &i: it->second) {
                        iter = docSec.find(doc[i]->getLeft()->getName());
                        if (iter != docSec.end() && (death > (depth[i] + depth[iter->second]))){
                            ind = {i, iter->second};
                            death = depth[i] + depth[iter->second];
                        }
                    }
                }
            }
        }
        if (ind.first == -100) {
            std::cout << "Proof is incorrect";
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
        std::cout << "Proof is incorrect";
        return 0;
    } else {
        auto tmp = docSec.find(base->getName());
        solve(tmp->second);
    }
    int cnt = 1;
    int zihh = zizi - 1;
    for (int i = 0; i < zizi; ++i) {
        std::cout << hypopotamus[i];
        if (i < zihh)
            std::cout << ',';
    }
    std::vector<int> shift(*(Answer.rbegin()) + 3);
    std::cout << "|- " << base->getName() << '\n';
    for (int i : Answer) {
        shift[i] = cnt;
        std::cout << "[" << cnt++ << ". ";
        switch (axioms[i].first) {
            case -1:
                std::cout << "Ax. sch. " << axioms[i].second << "] ";
                break;
            case -2:
                std::cout << "Hypothesis " << axioms[i].second << "] ";
                break;
            default:
                std::cout << "M.P. " << shift[axioms[i].first] << ", " << shift[axioms[i].second] << "] ";
                break;
        }
        std::cout << doc[i]->getName() << '\n';
    }
    return 0;
}