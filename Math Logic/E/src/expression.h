#include <utility>

#ifndef CPP_SOLUTION_EXPRESSION_H
#define CPP_SOLUTION_EXPRESSION_H

#include <string>
#include <vector>

const long long MOD = 6000000;

class expression {
public:
//    virtual std::string prefix_form() = 0;
    virtual char getType()  = 0;
    virtual expression* getLeft() = 0;
    virtual expression* getRight() = 0;
    virtual std::string getName() = 0;
    virtual int getIndex() = 0;
    virtual ~expression() = default;
};

std::vector<std::vector<expression*>> allTerms;

class variable : public expression {
public:
    std::string _name;
    char type = 'v';

    int getIndex() override {
        return {};
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

class unary : public expression {
public:
    expression* _left;
    expression* _right;
    char type = 'u';
    std::string _name = "";

    int getIndex() override {
        return {};
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
        if (_name.empty()) {
            if (type == '@') _name = "(@" + _left->getName() + "." + _right->getName() + ")";
            else _name = "(?" + _left->getName() + "." + _right->getName() + ")";
        }
        return _name;
    }

    unary(expression* left, expression* right, char ty) :
            _left(left),
            _right(right), type(ty) {

    }
//
//    virtual std::string prefixform() {
//        return "impl of (" + left->prefixform() + ") and (" + right->prefixform() + ")";
//    }
};

class function : public expression {
public:
    int _index;
    expression* _left;
    expression* _right = nullptr;
    char type = 'f';
    std::string _name = "";

    int getIndex() override {
        return _index;
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
        if (_name.empty()) {
            _name = "(" + _right->getName() + "(";
            for (int i = 0; i < allTerms[_index].size(); ++i) {
                _name += allTerms[_index][i]->getName();
                if (i < allTerms[_index].size() - 1) {
                    _name += ", ";
                }
            }
            _name += "))";
        }
        return _name;
    }

    function(expression* right, int index) :
            _right(right),
            _index(index) {

    }
//
//    virtual std::string prefixform() {
//        return "impl of (" + left->prefixform() + ") and (" + right->prefixform() + ")";
//    }
};

class predicat : public expression {
public:
    expression* _left;
    expression* _right;
    char type = 'p';
    std::string _name = "";

    int getIndex() override {
        return {};
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
        if (_name.empty()) _name ="(" +  _left->getName() + " = " + _right->getName() + ")";
        return _name;
    }

    predicat(expression* left, expression* right) :
            _left(left),
            _right(right) {

    }
//
//    virtual std::string prefixform() {
//        return "impl of (" + left->prefixform() + ") and (" + right->prefixform() + ")";
//    }
};

class slag : public expression {
public:
    expression* _left;
    expression* _right;
    char type = 'S';
    std::string _name = "";

    int getIndex() override {
        return {};
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
        if (_name.empty()) _name = "(" + _left->getName() + " * " + _right->getName() + ")";
        return _name;
    }

    slag(expression* left, expression* right) :
            _left(left),
            _right(right) {

    }
//
//    virtual std::string prefixform() {
//        return "impl of (" + left->prefixform() + ") and (" + right->prefixform() + ")";
//    }
};

class umno : public expression {
public:
    expression* _left;
    expression* _right = nullptr;
    char type = 'u';
    std::string _name = "";
    int _index;

    int getIndex() override {
        return _index;
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
        if (_name.empty()) {
            switch (type) {
                case '0':
                    _name = "0";
                    break;
                case '1':
                    _name = _right->getName() + "\'";
                    break;
                case 'F':
                    _name = "(" + _right->getName() + "(";
                    for (int i = 0; i < allTerms[_index].size(); ++i) {
                        _name += allTerms[_index][i]->getName();
                        if (i < allTerms[_index].size() - 1) {
                            _name += ", ";
                        }
                    }
                    _name += "))";
                    break;
            }
        }
        return _name;
    }

    umno(expression* left, expression* right, char ty) :
            _left(left),
            _right(right), type(ty) {
    }

    umno(expression* left, char ty) :
            _right(left), type(ty) {
    }

    umno(expression* left, int index, char ty) :
    _right(left),
    _index(index), type(ty) {

    }
//
//    virtual std::string prefixform() {
//        return "impl of (" + left->prefixform() + ") and (" + right->prefixform() + ")";
//    }
};


class term : public expression {
public:
    expression* _left;
    expression* _right;
    char type = 't';
    std::string _name = "";

    int getIndex() override {
        return {};
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
        if (_name.empty()) _name = "(" + _left->getName() + " + " + _right->getName() + ")";
        return _name;
    }

    term(expression* left, expression* right) :
            _left(left),
            _right(right) {

    }
//
//    virtual std::string prefixform() {
//        return "impl of (" + left->prefixform() + ") and (" + right->prefixform() + ")";
//    }
};

class implication : public expression {
public:
    expression* _left;
    expression* _right;
    char type = 'i';
    std::string _name = "";

    int getIndex() override {
        return {};
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
    std::string _name = "";

    int getIndex() override {
        return {};
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
    std::string _name = "";

    int getIndex() override {
        return {};
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
    std::string _name = "";

    int getIndex() override {
        return {};
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