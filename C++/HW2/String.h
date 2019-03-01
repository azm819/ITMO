#pragma once

#include <iostream>
#include <cstring>
#include <algorithm>

const char ASCII_NUL = '\0';

const int NUMBER_SYSTEM = 10;

const int MIN_ASCII_DIGIT = 48;
const int MAX_ASCII_DIGIT = 57;

const int MIN_ASCII_LOWCACE = 97;
const int MAX_ASCII_LOWCASE = 122;

const int MIN_ASCII_UPPERCASE = 65;
const int MAX_ASCII_UPPERCASE = 90;

class String {
public:
    explicit String(const char* str);
    String(const String& other);
    String(char symbol, size_t count);
    String();
    ~String();
    size_t getSize() const;
    void append(const String& other);
    void append(const char* s);
    void append(const int& i);
    void append(const char& c);
    String substring(int start, int end) const;
    String postfix(int start) const;
    String suffix(int ending) const;
    char charAt(int pos) const;
    void reverse();
    std::string toString() const;
    void print() const;
    void swap(String& first, String& second);
    int find(char c) const;
    int rfind(char c) const;
    bool isDigit() const;
    bool isAlpha() const;

    String& operator=(String other);
    String& operator+=(String& other);
private:
    char* mStr;
    size_t mSize;
};
