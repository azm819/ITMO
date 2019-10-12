#include <iostream>
#include <set>
#include <map>
#include <vector>

#include "proofs.h"


using std::string;
using std::cout;
using std::cin;

std::vector<string> Variables;

expression *parse(string &str, size_t begin, size_t end);

expression *combNeg(string &str, size_t begin, size_t end, int times) {
    if (times > 0) {
//        cout << "Neg: " << str.substr(begin + 1, end - 1 - begin) << '\n';
        return new negation(combNeg(str, begin + 1, end, times - 1));
    }
    return parse(str, begin, end);
}

int parseNeg(string &str, size_t begin, size_t end, size_t start) {
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

expression *parseImp(string &str, size_t begin, size_t end, size_t start) {
//    cout << str.substr(begin, start - 2 - begin) << " Impl " << str.substr(start, end - start) << '\n';
    return new implication(parse(str, begin, start - 2), parse(str, start, end));
}

expression *parseDis(string &str, size_t begin, size_t end, size_t start) {
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
//    cout << str.substr(begin, start - begin) << " Dis " << str.substr(start, end - start) << '\n';
    return new disjunction(parse(str, begin, start - 1), parse(str, start, end));
}

expression *parseCon(string &str, size_t begin, size_t end, size_t start) {
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
//    cout << str.substr(begin, start - 1 - begin) << " Con " << str.substr(start, end - start) << '\n';
    return new conjunction(parse(str, begin, start - 1), parse(str, start, end));
}


expression *parse(string &str, size_t begin, size_t end) {
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
//    cout << "Var: " << str.substr(begin, end - begin) << '\n';
    string newStr = str.substr(begin, end - begin);
    return new variable(newStr);
}

void deleteSpaces(string &str) {
    for (int i = 0; i < str.length(); ++i)
        if (str[i] == ' ') {
            str.erase(i, 1);
            i--;
        }
}

std::set<string> oldVars;
//std::map <string, string> newVars;
std::vector<std::vector<expression *>> docs;
std::vector<bool> evalVars;

void getVars(expression *expr) {
    if (expr->getType() == 'v') {
        oldVars.insert(expr->getName());
        return;
    }
    if (expr->getType() == 'n') {
        getVars(expr->getRight());
        return;
    }
    getVars(expr->getLeft());
    getVars(expr->getRight());
}

//void setVars(expression* expr) {
//    if (expr->getType() == 'v'){
//        expr->setName(newVars[expr->getName()]);
//        return;
//    }
//    if (expr->getType() == 'n') {
//        setVars(expr->getRight());
//        return;
//    }
//    setVars(expr->getLeft());
//    setVars(expr->getRight());
//}

bool evaluateExpr(expression *expr, std::vector<expression *> &doc, bool A, bool B = false, bool C = false) {
    if (expr->getType() == 'v') {
        if (expr->getName() == Variables[0]) {
            return A;
        }
        if (expr->getName() == Variables[1]) {
            return B;
        }
        if (expr->getName() == Variables[2]) {
            return C;
        }
        return false;
    }
    if (expr->getType() == 'n') {
        if (evaluateExpr(expr->getRight(), doc, A, B, C)) {
            yesA_Neg(expr->getRight(), doc);
            return false;
        }
        notA_Neg(expr->getRight(), doc);
        return true;
    }
    if (expr->getType() == 'c') {
        if (evaluateExpr(expr->getLeft(), doc, A, B, C)) {
            if (evaluateExpr(expr->getRight(), doc, A, B, C)) {
                yesA_yesB_Con(expr->getLeft(), expr->getRight(), doc);
                return true;
            } else {
                yesA_notB_Con(expr->getLeft(), expr->getRight(), doc);
                return false;
            }
        } else {
            if (evaluateExpr(expr->getRight(), doc, A, B, C)) {
                notA_yesB_Con(expr->getLeft(), expr->getRight(), doc);
                return false;
            } else {
                notA_notB_Con(expr->getLeft(), expr->getRight(), doc);
                return false;
            }
        }
    }
    if (expr->getType() == 'd') {
        if (evaluateExpr(expr->getLeft(), doc, A, B, C)) {
            if (evaluateExpr(expr->getRight(), doc, A, B, C)) {
                yesA_yesB_Dis(expr->getLeft(), expr->getRight(), doc);
                return true;
            } else {
                yesA_notB_Dis(expr->getLeft(), expr->getRight(), doc);
                return true;
            }
        } else {
            if (evaluateExpr(expr->getRight(), doc, A, B, C)) {
                notA_yesB_Dis(expr->getLeft(), expr->getRight(), doc);
                return true;
            } else {
                notA_notB_Dis(expr->getLeft(), expr->getRight(), doc);
                return false;
            }
        }
    }
    if (expr->getType() == 'i') {
        if (evaluateExpr(expr->getLeft(), doc, A, B, C)) {
            if (evaluateExpr(expr->getRight(), doc, A, B, C)) {
                yesA_yesB_Imp(expr->getLeft(), expr->getRight(), doc);
                return true;
            } else {
                yesA_notB_Imp(expr->getLeft(), expr->getRight(), doc);
                return false;
            }
        } else {
            if (evaluateExpr(expr->getRight(), doc, A, B, C)) {
                notA_yesB_Imp(expr->getLeft(), expr->getRight(), doc);
                return true;
            } else {
                notA_notB_Imp(expr->getLeft(), expr->getRight(), doc);
                return true;
            }
        }
    }
    return false;
}

int main() {
    string str;
    getline(cin, str);
    deleteSpaces(str);
    auto expr = parse(str, 0, str.length());
    if (check(expr) > 0) {
        cout << "|- " << str << '\n' << str;
        return 0;
    }
    getVars(expr);
    for (auto i: oldVars) {
        Variables.push_back(i);
    }
    Variables.emplace_back(Variables[0]);
    Variables.emplace_back(Variables[1]);
    Variables.emplace_back(Variables[2]);
    auto yesA = new variable(Variables[0]);
    auto yesB = new variable(Variables[1]);
    auto yesC = new variable(Variables[2]);
    auto notA = new negation(yesA);
    auto notB = new negation(yesB);
    auto notC = new negation(yesC);
    std::vector<expression *> answer;
    std::vector<std::pair<int, int>> axioms;
    std::vector<expression *> hypo = {yesA, yesB, yesC, notA, notB, notC};
    switch (oldVars.size()) {
        case 1: {
            docs.resize(2);
            evalVars.resize(2);
            if (evaluateExpr(expr, docs[1], 1)) { // A - true
                if (evaluateExpr(expr, docs[0], 0)) { // !A - true
                    std::vector<expression *> res;
                    deduct(Variables[0], docs[1], docs[0], res, {});
                    cout << "|- " << expr->getName() << '\n';
                    minimize(res, hypo, answer, axioms);
                    for (auto &i: Answer) {
                        cout << answer[i]->getName() << '\n';
                    }
                } else { // !A - false
                    cout << "" + Variables[0] + "|- " << expr->getName() << '\n';
                    minimize(docs[1], hypo, answer, axioms);
                    for (auto &i: Answer) {
                        cout << answer[i]->getName() << '\n';
                    }
                }
                return 0;
            }
            break;
        }
        case 2: {
            docs.resize(4);
            evalVars.resize(4);
            evalVars[0] = evaluateExpr(expr, docs[0], 0, 0); // !A !B
            evalVars[1] = evaluateExpr(expr, docs[1], 0, 1); // !A  B
            evalVars[2] = evaluateExpr(expr, docs[2], 1, 0); //  A !B
            evalVars[3] = evaluateExpr(expr, docs[3], 1, 1); //  A  B
            if (evalVars[3]) {
                if (evalVars[1]) {
                    std::vector<expression *> withoutAyesB;
                    deduct(Variables[0], docs[3], docs[1], withoutAyesB, {yesB});
                    if (evalVars[2] && evalVars[0]) {
                        // calculate doc[0]
                        std::vector<expression *> withoutAnotB;
                        deduct(Variables[0], docs[2], docs[0], withoutAnotB, {notB});
                        std::vector<expression *> result;
                        deduct(Variables[1], withoutAyesB, withoutAnotB, result, {});
                        cout << "|- " << expr->getName() << '\n';
                        minimize(result, hypo, answer, axioms);
                        for (auto &i: Answer) {
                            cout << answer[i]->getName() << '\n';
                        }
                    } else {
                        cout << "" + Variables[1] + " |- " << expr->getName() << '\n';
                        minimize(withoutAyesB, hypo, answer, axioms);
                        for (auto &i: Answer) {
                            cout << answer[i]->getName() << '\n';
                        }
                    }
                } else {
                    if (evalVars[2]) {
                        std::vector<expression *> result;
                        deduct(Variables[1], docs[3], docs[2], result, {yesA});
                        cout << "" + Variables[0] + "|- " << expr->getName() << '\n';
                        minimize(result, hypo, answer, axioms);
                        for (auto &i: Answer) {
                            cout << answer[i]->getName() << '\n';
                        }
                    } else {
                        cout << "" + Variables[0] + ", " + Variables[1] + " |- " << expr->getName() << '\n';
                        minimize(docs[3], hypo, answer, axioms);
                        for (auto &i: Answer) {
                            cout << answer[i]->getName() << '\n';
                        }
                    }
                }
                return 0;
            }
            break;
        }
        case 3: {
            docs.resize(8);
            evalVars.resize(8);
            evalVars[0] = evaluateExpr(expr, docs[0], 0, 0, 0); // !A !B !C
            evalVars[1] = evaluateExpr(expr, docs[1], 0, 0, 1); // !A !B  C
            evalVars[2] = evaluateExpr(expr, docs[2], 0, 1, 0); // !A  B !C
            evalVars[3] = evaluateExpr(expr, docs[3], 0, 1, 1); // !A  B  C
            evalVars[4] = evaluateExpr(expr, docs[4], 1, 0, 0); //  A !B !C
            evalVars[5] = evaluateExpr(expr, docs[5], 1, 0, 1); //  A !B  C
            evalVars[6] = evaluateExpr(expr, docs[6], 1, 1, 0); //  A  B !C
            evalVars[7] = evaluateExpr(expr, docs[7], 1, 1, 1); //  A  B  C
            if (evalVars[7]) {
                if (evalVars[3]) {
                    std::vector<expression *> withoutAyesByesC;
                    deduct(Variables[0], docs[7], docs[3], withoutAyesByesC, {yesB, yesC});
                    if (evalVars[5] && evalVars[1]) {
                        std::vector<expression *> withoutAnotByesC;
                        deduct(Variables[0], docs[5], docs[1], withoutAnotByesC, {notB, yesC});
                        std::vector<expression *> withoutAByesC;
                        deduct(Variables[1], withoutAyesByesC, withoutAnotByesC, withoutAByesC, {yesC});
                        if (evalVars[6] && evalVars[2] && evalVars[0] && evalVars[4]) {
                            std::vector<expression *> withoutAyesBnotC;
                            deduct(Variables[0], docs[6], docs[2], withoutAyesBnotC, {yesB, notC});
                            std::vector<expression *> withoutAnotBnotC;
                            deduct(Variables[0], docs[4], docs[0], withoutAnotBnotC, {notB, notC});
                            std::vector<expression *> withoutABnotC;
                            deduct(Variables[1], withoutAyesBnotC, withoutAnotBnotC, withoutABnotC, {notC});
                            std::vector<expression *> result;
                            deduct(Variables[2], withoutAByesC, withoutABnotC, result, {});
                            cout << "|- " << expr->getName() << '\n';
                            minimize(result, hypo, answer, axioms);
                            for (auto &i: Answer) {
                                cout << answer[i]->getName() << '\n';
                            }
                        } else {
                            cout << "" + Variables[2] + " |- " << expr->getName() << '\n';
                            minimize(withoutAByesC, hypo, answer, axioms);
                            for (auto &i: Answer) {
                                cout << answer[i]->getName() << '\n';
                            }
                        }
                    } else if (evalVars[6] && evalVars[2]) {
                        std::vector<expression *> withoutAyesBnotC;
                        deduct(Variables[0], docs[6], docs[2], withoutAyesBnotC, {yesB, notC});
                        std::vector<expression *> result;
                        deduct(Variables[2], withoutAyesByesC, withoutAyesBnotC, result, {yesB});
                        cout << "" + Variables[1] + " |- " << expr->getName() << '\n';
                        minimize(result, hypo, answer, axioms);
                        for (auto &i: Answer) {
                            cout << answer[i]->getName() << '\n';
                        }
                    } else {
                        cout << "" + Variables[1] + ", " + Variables[2] + " |- " << expr->getName() << '\n';
                        minimize(withoutAyesByesC, hypo, answer, axioms);
                        for (auto &i: Answer) {
                            cout << answer[i]->getName() << '\n';
                        }
                    }
                } else if (evalVars[5]) {
                    std::vector<expression *> withoutByesC;
                    deduct(Variables[1], docs[7], docs[5], withoutByesC, {yesA, yesC});
                    if (evalVars[6] && evalVars[4]) {
                        std::vector<expression *> withoutBnotC;
                        deduct(Variables[1], docs[6], docs[4], withoutBnotC, {yesA, notC});
                        std::vector<expression *> result;
                        deduct(Variables[2], withoutByesC, withoutBnotC, result, {yesA});
                        cout << "" + Variables[0] + " |- " << expr->getName() << '\n';
                        minimize(result, hypo, answer, axioms);
                        for (auto &i: Answer) {
                            cout << answer[i]->getName() << '\n';
                        }
                    } else {
                        cout << "" + Variables[0] + ", " + Variables[2] + " |- " << expr->getName() << '\n';
                        minimize(withoutByesC, hypo, answer, axioms);
                        for (auto &i: Answer) {
                            cout << answer[i]->getName() << '\n';
                        }
                    }
                } else if (evalVars[6]) {
                    std::vector<expression *> result;
                    deduct(Variables[2], docs[7], docs[6], result, {yesA, yesB});
                    cout << "" + Variables[0] + ", " + Variables[1] + " |- " << expr->getName() << '\n';
                    minimize(result, hypo, answer, axioms);
                    for (auto &i: Answer) {
                        cout << answer[i]->getName() << '\n';
                    }
                } else {
                    cout << "" + Variables[0] + ", " + Variables[1] + ", " + Variables[2] + " |- " << expr->getName()
                         << '\n';
                    minimize(docs[7], hypo, answer, axioms);
                    for (auto &i: Answer) {
                        cout << answer[i]->getName() << '\n';
                    }
                }
                return 0;
            }
            break;
        }
        default:
            break;
    }
    expr = new negation(expr);
    docs.clear();
    evalVars.clear();
    switch (oldVars.size()) {
        case 1: {
            docs.resize(2);
            evalVars.resize(2);
            if (evaluateExpr(expr, docs[0], 0)) { // !A - true
                if (evaluateExpr(expr, docs[1], 1)) { // A - true
                    std::vector<expression *> res;
                    deduct(Variables[0], docs[1], docs[0], res, {});
                    cout << "|- " << expr->getName() << '\n';
                    minimize(res, hypo, answer, axioms);
                    for (auto &i: Answer) {
                        cout << answer[i]->getName() << '\n';
                    }
                } else { // A - false
                    cout << "!" + Variables[0] + " |- " << expr->getName() << '\n';
                    minimize(docs[0], hypo, answer, axioms);
                    for (auto &i: Answer) {
                        cout << answer[i]->getName() << '\n';
                    }
                }
                return 0;
            }
            break;
        }
        case 2: {
            docs.resize(4);
            evalVars.resize(4);
            evalVars[0] = evaluateExpr(expr, docs[0], 0, 0); // !A !B
            evalVars[1] = evaluateExpr(expr, docs[1], 0, 1); // !A  B
            evalVars[2] = evaluateExpr(expr, docs[2], 1, 0); //  A !B
            evalVars[3] = evaluateExpr(expr, docs[3], 1, 1); //  A  B
            if (evalVars[0]) {
                if (evalVars[2]) {
                    std::vector<expression *> withoutAnotB;
                    deduct(Variables[0], docs[2], docs[0], withoutAnotB, {notB});
                    if (evalVars[1] && evalVars[3]) {
                        // calculate doc[0]
                        std::vector<expression *> withoutAyesB;
                        deduct(Variables[0], docs[3], docs[1], withoutAyesB, {yesB});
                        std::vector<expression *> result;
                        deduct(Variables[1], withoutAyesB, withoutAnotB, result, {});
                        cout << "|- " << expr->getName() << '\n';
                        minimize(result, hypo, answer, axioms);
                        for (auto &i: Answer) {
                            cout << answer[i]->getName() << '\n';
                        }
                    } else {
                        cout << "!" + Variables[1] + " |- " << expr->getName() << '\n';
                        minimize(withoutAnotB, hypo, answer, axioms);
                        for (auto &i: Answer) {
                            cout << answer[i]->getName() << '\n';
                        }
                    }
                } else {
                    if (evalVars[1]) {
                        std::vector<expression *> result;
                        deduct(Variables[1], docs[1], docs[0], result, {notA});
                        cout << "!" + Variables[0] + " |- " << expr->getName() << '\n';
                        minimize(result, hypo, answer, axioms);
                        for (auto &i: Answer) {
                            cout << answer[i]->getName() << '\n';
                        }
                    } else {
                        cout << "!" + Variables[0] + ", !" + Variables[1] + " |- " << expr->getName() << '\n';
                        minimize(docs[0], hypo, answer, axioms);
                        for (auto &i: Answer) {
                            cout << answer[i]->getName() << '\n';
                        }
                    }
                }
                return 0;
            }
            break;
        }
        case 3: {
            docs.resize(8);
            evalVars.resize(8);
            evalVars[0] = evaluateExpr(expr, docs[0], 0, 0, 0); // !A !B !C
            evalVars[1] = evaluateExpr(expr, docs[1], 0, 0, 1); // !A !B  C
            evalVars[2] = evaluateExpr(expr, docs[2], 0, 1, 0); // !A  B !C
            evalVars[3] = evaluateExpr(expr, docs[3], 0, 1, 1); // !A  B  C
            evalVars[4] = evaluateExpr(expr, docs[4], 1, 0, 0); //  A !B !C
            evalVars[5] = evaluateExpr(expr, docs[5], 1, 0, 1); //  A !B  C
            evalVars[6] = evaluateExpr(expr, docs[6], 1, 1, 0); //  A  B !C
            evalVars[7] = evaluateExpr(expr, docs[7], 1, 1, 1); //  A  B  C
            if (evalVars[0]) {
                if (evalVars[4]) { // delete A
                    std::vector<expression *> withoutAnotBnotC;
                    deduct(Variables[0], docs[4], docs[0], withoutAnotBnotC, {notB, notC});
                    if (evalVars[2] && evalVars[6]) { // delete B
                        std::vector<expression *> withoutAyesBnotC;
                        deduct(Variables[0], docs[6], docs[2], withoutAyesBnotC, {yesB, notC});
                        std::vector<expression *> withoutABnotC;
                        deduct(Variables[1], withoutAyesBnotC, withoutAnotBnotC, withoutABnotC, {notC});
                        if (evalVars[1] && evalVars[5] && evalVars[7] && evalVars[3]) { // delete C
                            std::vector<expression *> withoutAnotByesC;
                            deduct(Variables[0], docs[5], docs[1], withoutAnotByesC, {notB, yesC});
                            std::vector<expression *> withoutAyesByesC;
                            deduct(Variables[0], docs[7], docs[3], withoutAyesByesC, {yesB, yesC});
                            std::vector<expression *> withoutAByesC;
                            deduct(Variables[1], withoutAyesByesC, withoutAnotByesC, withoutAByesC, {yesC});
                            std::vector<expression *> result;
                            deduct(Variables[2], withoutAByesC, withoutABnotC, result, {});
                            cout << "|- " << expr->getName() << '\n';
                            minimize(result, hypo, answer, axioms);
                            for (auto &i: Answer) {
                                cout << answer[i]->getName() << '\n';
                            }
                        } else {
                            cout << "!" + Variables[2] + " |- " << expr->getName() << '\n';
                            minimize(withoutABnotC, hypo, answer, axioms);
                            for (auto &i: Answer) {
                                cout << answer[i]->getName() << '\n';
                            }
                        }
                    } else if (evalVars[1] && evalVars[5]) { // delete C
                        std::vector<expression *> withoutAnotByesC;
                        deduct(Variables[0], docs[5], docs[1], withoutAnotByesC, {notB, yesC});
                        std::vector<expression *> result;
                        deduct(Variables[2], withoutAnotByesC, withoutAnotBnotC, result, {notB});
                        cout << "!" + Variables[1] + " |- " << expr->getName() << '\n';
                        minimize(result, hypo, answer, axioms);
                        for (auto &i: Answer) {
                            cout << answer[i]->getName() << '\n';
                        }
                    } else {
                        cout << "!" + Variables[1] + ", !" + Variables[2] + " |- " << expr->getName() << '\n';
                        minimize(withoutAnotBnotC, hypo, answer, axioms);
                        for (auto &i: Answer) {
                            cout << answer[i]->getName() << '\n';
                        }
                    }
                } else if (evalVars[2]) { // delete B
                    std::vector<expression *> withoutBnotC;
                    deduct(Variables[1], docs[2], docs[0], withoutBnotC, {notA, notC});
                    if (evalVars[1] && evalVars[3]) { // delete C
                        std::vector<expression *> withoutByesC;
                        deduct(Variables[1], docs[3], docs[1], withoutByesC, {notA, yesC});
                        std::vector<expression *> result;
                        deduct(Variables[2], withoutByesC, withoutBnotC, result, {notA});
                        cout << "!" + Variables[0] + " |- " << expr->getName() << '\n';
                        minimize(result, hypo, answer, axioms);
                        for (auto &i: Answer) {
                            cout << answer[i]->getName() << '\n';
                        }
                    } else {
                        cout << "!" + Variables[0] + ", !" + Variables[2] + " |- " << expr->getName() << '\n';
                        minimize(withoutBnotC, hypo, answer, axioms);
                        for (auto &i: Answer) {
                            cout << answer[i]->getName() << '\n';
                        }
                    }
                } else if (evalVars[1]) {
                    std::vector<expression *> result;
                    deduct(Variables[2], docs[1], docs[0], result, {notA, notB});
                    cout << "!" + Variables[0] + ", !" + Variables[1] + " |- " << expr->getName() << '\n';
                    minimize(result, hypo, answer, axioms);
                    for (auto &i: Answer) {
                        cout << answer[i]->getName() << '\n';
                    }
                } else {
                    cout << "!" + Variables[0] + ", !" + Variables[1] + ", !" + Variables[2] + " |- " << expr->getName()
                         << '\n';
                    minimize(docs[0], hypo, answer, axioms);
                    for (auto &i: Answer) {
                        cout << answer[i]->getName() << '\n';
                    }
                }
                return 0;
            }
            break;
        }
        default:
            break;
    }
    cout << ":(\n";
    return 0;
}