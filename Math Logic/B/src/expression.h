#ifndef CPP_SOLUTION_EXPRESSION_H
#define CPP_SOLUTION_EXPRESSION_H

#include <string>

const long long MOD = 6000000;

class expression {
public:
//    virtual std::string prefix_form() = 0;
    virtual char getType()  = 0;
    virtual expression* getLeft() = 0;
    virtual expression* getRight() = 0;
    virtual std::string getName() = 0;
    virtual unsigned long long getDepth() = 0;
    virtual ~expression() = default;;
};

class variable : public expression {
public:
    std::string _name;
    char type = 'v';
    unsigned long long depth = 0;

    unsigned long long getDepth() override{
        if (depth == 0) depth = _name.size();
        return depth;
    }

    char getType() override{
        return type;
    }

    expression* getLeft() override{return nullptr;};
    expression* getRight() override{return nullptr;};


    std::string getName() override{
        return _name;
    }

    explicit variable(std::string &name) : _name(name) {

//        for (char & i : _name){
//            if (i == 'a') i = '\'';
//        }
    }

//    virtual std::string prefixform() {
//        return _name;
//    }
};

class implication : public expression {
public:
    expression* _left;
    expression* _right;
    char type = 'i';
    unsigned long long depth = 0;
    std::string _name = "";

    unsigned long long getDepth() override{
        if (depth == 0) depth = (_left->getDepth() + _right->getDepth() ) % MOD * 2 + 3;
        return depth;
    }

    char getType() override{
        return type;
    }

    expression* getRight() override{
        return _right;
    }

    expression* getLeft() override{
        return _left;
    }

    std::string getName() override{
        if (_name.empty()) _name = "(" + _left->getName() + " -> " + _right->getName() + ")";
        return _name;
    }

    implication(expression* left, expression* right) :
            _left(left),
            _right(right) {

    }
//
//    virtual std::string prefixform() {
//        return "impl of (" + left->prefixform() + ") and (" + right->prefixform() + ")";
//    }
};

class disjunction : public expression {
public:
    expression* _left;
    expression* _right;
    char type = 'd';
    unsigned long long depth = 0;
    std::string _name = "";

    unsigned long long getDepth() override{
        if (depth == 0) depth = (_left->getDepth()  + _right->getDepth()) % MOD * 3 + 5;
        return depth;
    }


    char getType() override{
        return type;
    }

    expression* getRight() override{
        return _right;
    }

    expression* getLeft() override{
        return _left;
    }

    std::string getName() override{
        if (_name.empty()) _name = "(" + _left->getName() + " | " + _right->getName() + ")";
        return _name;
    }

    disjunction(expression* left, expression* right) :
            _left(left),
            _right(right) {

    }
//
//    virtual std::string prefixform() {
//        return "disj of (" + left->prefixform() + ") and (" + right->prefixform() + ")";
//    }
};

class conjunction : public expression {
public:
    expression* _left;
    expression* _right;
    char type = 'c';
    unsigned long long depth = 0;
    std::string _name = "";

    unsigned long long getDepth() override{
        if (depth == 0) depth = (_left->getDepth() + _right->getDepth()) % MOD * 7 + 9;
        return depth;
    }


    char getType() override{
        return type;
    }

    expression* getRight() override{
        return _right;
    }

    expression* getLeft() override {
        return  _left;
    };

    std::string getName() override{
        if (_name.empty()) _name = "(" + _left->getName() + " & " + _right->getName() + ")";
        return _name;
    }

    conjunction(expression* left, expression* right) :
            _left(left),
            _right(right) {

    }

//    virtual std::string prefixform() {
//        return "conj of (" + left->prefixform() + ") and (" + right->prefixform() + ")";
//    }
};


class negation : public expression {
public:
    expression* _expr;
    char type = 'n';
    unsigned long long depth = 0;
    std::string _name = "";

    unsigned long long getDepth() override{
        if (depth == 0) depth = _expr->getDepth() % MOD * 13  + 17;
        return depth;
    }


    char getType() override{
        return type;
    }

    expression* getRight() override{
        return _expr;
    }


    expression* getLeft() override {
        return _expr;
    };

    std::string getName() override{
        if (_name.empty()) _name = "!" + _expr->getName();
        return _name;
    }

    explicit negation(expression* expr) :
            _expr(expr) {

    }

//    virtual std::string prefixform() {
//        return "neg of (" + expr->prefixform() + ")";
//    }
};

#endif //CPP_SOLUTION_EXPRESSION_H