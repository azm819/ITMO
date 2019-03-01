#pragma once

#include <cstddef>
#include <string>

#include "Array.hpp"
#include "Functions.hpp"


template<typename Tx>
struct X {
    X() {
        this->x_ = new Tx();
        *this->x_ = 1;
    }

    X(const X &inX) {
        this->x_ = new Tx();
        *this->x_ = *inX.x_;
    }

    ~X() { delete this->x_; }

    friend std::ostream &operator<<(std::ostream &s, const X &obj) {
        s << *(obj.x_);
        return s;
    }

    void set(Tx i) {
        *(this->x_) = i;
    }

private:
    X &operator=(const X &inX);

    Tx *x_;
};


/******************************T E S T *********************/
void test0();

void test1();

void test2();

void test3();

void test4();

void test5();

void test6();

void test7();

int test() {
    test0();
    test1();
    test2();
    test3();
    test4();
    test5();
    test6();
    test7();

    return 0;
}

void test0() {
    std::cout << std::endl << "*****Test 0(primitives)**********" << std::endl;
    {
        std::cout << std::endl << "*****CHAR**********" << std::endl;
        Array<char> ar(size_t(5), '0');
        Array<char> x(size_t(4), '4');
        ar = x;
        flatten(ar, std::cout);
        std::cout << std::endl;

        Array<char> x2(size_t(6), '6');
        ar = x2;
        flatten(ar, std::cout);
        std::cout << std::endl;
    }
    std::cout << std::endl;
    {
        std::cout << std::endl << "*****STRING**********" << std::endl;
        Array<std::string> cr(size_t(5), "0");
        Array<std::string> cx(size_t(4), "4");
        cr = cx;
        flatten(cr, std::cout);
        std::cout << std::endl;

        Array<std::string> cx2(size_t(6), "6");
        cr = cx2;
        flatten(cr, std::cout);
        std::cout << std::endl;
    }
    std::cout << std::endl;
    {
        std::cout << std::endl << "*****INT**********" << std::endl;
        Array<int> ir(size_t(5), 0);
        Array<int> ix(size_t(4), 4);
        ir = ix;
        flatten(ir, std::cout);
        std::cout << std::endl;

        Array<int> ix2(size_t(6), 6);
        ir = ix2;
        flatten(ir, std::cout);
        std::cout << std::endl;
    }
    std::cout << std::endl;
    {
        std::cout << std::endl << "*****DOUBLE**********" << std::endl;
        Array<double> dr(size_t(5), 0.0);
        Array<double> dx(size_t(4), 4.0);
        dr = dx;
        flatten(dr, std::cout);
        std::cout << std::endl;

        Array<double> ix2(size_t(6), 6.0);
        dr = ix2;
        flatten(dr, std::cout);
        std::cout << std::endl;
    }
    std::cout << std::endl;
    return;
}


void test1() {
    {
        std::cout << std::endl << "*****Test 1(assigment)**********" << std::endl;
        Array<char> ar(size_t(100), '0');
        Array<char> x(size_t(0), '1');
        ar = x;
        flatten(ar, std::cout);
        std::cout << std::endl;
    }
    {
        std::cout << "*****STRING**********" << std::endl;
        Array<std::string> cr(size_t(100), "Str0");
        Array<std::string> cx(size_t(0), "Str1");
        cr = cx;
        flatten(cr, std::cout);
        std::cout << std::endl;

        Array<std::string> cx2(size_t(2), "Str3");
        cr = cx2;
        flatten(cr, std::cout);
        std::cout << std::endl;
    }
    {
        std::cout << "*****INT**********" << std::endl;
        Array<int> cr(size_t(100), 0);
        Array<int> cx(size_t(0), 15);
        cr = cx;
        flatten(cr, std::cout);
        std::cout << std::endl;

        Array<int> cx2(size_t(2), 55);
        cr = cx2;
        flatten(cr, std::cout);
        std::cout << std::endl;
    }
    return;
}

void test2() {
    std::cout << std::endl << "*****Test 2(copy constructor)**********" << std::endl;
    {
        std::cout << "*****CHAR**********" << std::endl;
        Array<char> x(size_t(3), '3');
        Array<char> ar(x);
        flatten(ar, std::cout);
        std::cout << std::endl;
    }
    {
        std::cout << "*****STRING**********" << std::endl;
        Array<std::string> x(size_t(3), "333");
        Array<std::string> ar(x);
        flatten(ar, std::cout);
        std::cout << std::endl;
    }

    return;
}

void test3() {
    std::cout << std::endl << "*****Test 3(Empty)**********" << std::endl;
    {
        std::cout << "*****CHAR**********" << std::endl;
        Array<char> ar(size_t(0), '0');
        ar = ar;
        flatten(ar, std::cout);
        std::cout << std::endl;
    }
    {
        std::cout << "*****STRING**********" << std::endl;
        Array<std::string> ar(size_t(0), "0");
        ar = ar;
        flatten(ar, std::cout);
        std::cout << std::endl;
    }
    return;
}

void test4() {
    std::cout << std::endl << "*****Test 4(assigment A=A) **********" << std::endl;
    {
        Array<char> ar(size_t(4), '0');
        ar = ar;
        flatten(ar, std::cout);
        std::cout << std::endl;
    }
    return;
}

void test5() {
    std::cout << std::endl << "*****Test 5(out bound)**********" << std::endl;
    {
        std::cout << "*****more**********" << std::endl;
        Array<char> ar(size_t(4), '0');
        std::cout << ar[10] << std::endl;
    }
    {
        std::cout << "*****lesse**********" << std::endl;
        Array<char> ar(size_t(4), '0');
        std::cout << ar[-10] << std::endl;
    }
    return;
}

void test6() {
    std::cout << std::endl << "*****Test 6(pointer)**********" << std::endl;
    {
        std::cout << "*****CHAR(copy)**********" << std::endl;
        Array<char> *ar = new Array<char>(size_t(4), '4');
        flatten(*ar, std::cout);
        std::cout << std::endl;
        delete ar;
    }
    {
        std::cout << "*****CHAR(=)**********" << std::endl;
        Array<char> *ar = new Array<char>(size_t(5), '5');
        flatten(*ar, std::cout);
        std::cout << std::endl;
        Array<char> *xr = ar;
        flatten(*xr, std::cout);
        std::cout << std::endl;
        delete ar;
    }
    return;
}

void test7() {
    std::cout << std::endl << "*****Test 7(X-object)**********" << std::endl;
    {
        std::cout << "***** X<INT> **********" << std::endl;
        X<int> x;
        x.set(4);
        Array<X<int>> *ar = new Array<X<int>>(size_t(4), x);
        flatten(*ar, std::cout);
        std::cout << std::endl;
        delete ar;
    }
    {
        std::cout << "***** X<CHAR> (new, =, copy) **********" << std::endl;
        X<char> x;
        x.set('c');
        Array<X<char>> *ar = new Array<X<char>>(size_t(4), x);
        flatten(*ar, std::cout);
        std::cout << std::endl;
        Array<X<char>> *xr = ar;
        flatten(*xr, std::cout);
        std::cout << std::endl;
        Array<X<char>> y(*xr);
        flatten(y, std::cout);
        std::cout << std::endl;
        delete ar;
    }
    {
        std::cout << "***** X<STRING> (new, =, copy)**********" << std::endl;
        X<std::string> x;
        x.set("There are no tests for this task");
        Array<X<std::string>> *ar = new Array<X<std::string>>(size_t(1), x);
        flatten(*ar, std::cout);
        std::cout << std::endl;
        Array<X<std::string>> *xr = ar;
        flatten(*xr, std::cout);
        std::cout << std::endl;
        Array<X<std::string>> y(*xr);
        flatten(y, std::cout);
        std::cout << std::endl;
        delete ar;
    }
    return;
}