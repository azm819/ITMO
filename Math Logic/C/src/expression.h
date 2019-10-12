#ifndef CPP_SOLUTION_EXPRESSION_H
#define CPP_SOLUTION_EXPRESSION_H

#include <string>

class expression {
public:
//    virtual std::string prefix_form() = 0;
    virtual char getType()  = 0;
    virtual expression* getLeft() = 0;
    virtual expression* getRight() = 0;
    virtual std::string getName() = 0;
    virtual ~expression() = default;;
};

class variable : public expression {
public:
    std::string _name;
    char type = 'v';

    char getType() override{
        return type;
    }

    expression* getLeft() override{return nullptr;};
    expression* getRight() override{return nullptr;};


    std::string getName() override{
        return _name;
    }

    explicit variable(std::string &name) : _name(name) {
        for (char & i : _name){
            if (i == 'a') i = '\'';
        }
    }

//    virtual std::string prefixform() {
//        return _name;
//    }
};

class implication : public expression {
public:
    expression* _left;
    expression* _right;
    std::string _name;
    char type = 'i';

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
        return "(" + _left->getName() + " -> " + _right->getName() + ")";
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
        return "(" + _left->getName() + " | " + _right->getName() + ")";
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
        return "(" + _left->getName() + " & " + _right->getName() + ")";
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
        return "!" + _expr->getName();
    }

    explicit negation(expression* expr) :
            _expr(expr) {
    }

//    virtual std::string prefixform() {
//        return "neg of (" + expr->prefixform() + ")";
//    }
};

#endif //CPP_SOLUTION_EXPRESSION_H