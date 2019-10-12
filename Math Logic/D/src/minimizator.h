#ifndef MLD_MINIMIZATOR_H
#define MLD_MINIMIZATOR_H

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

const int INF = 1000000000;
std::set<int> Answer;

void solve(int ind, std::vector<std::pair<int, int>> &axioms) {
    Answer.insert(ind);
    if (axioms[ind].first == -1 || axioms[ind].first == -2) {
        return;
    }
    solve(axioms[ind].second, axioms);
    solve(axioms[ind].first, axioms);
}

void minimize(const std::vector<expression *> &vec, const std::vector<expression *> &hypothesis,
              std::vector<expression *> &doc, std::vector<std::pair<int, int>> &axioms) {
    Answer.clear();
    std::vector<long long> depth;
    std::map<std::string, int> docSec;
    std::map<std::string, std::vector<int>> ModusPonis;
    int zizi = hypothesis.size();
    int sizik = 0;
    std::string ResStr;
    for (auto result: vec) {
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
                    continue;
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
        if (ind.first == -100) {
            continue;
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
    auto tmp = docSec.find(vec.back()->getName());
    solve(tmp->second, axioms);
}

#endif //MLD_MINIMIZATOR_H
