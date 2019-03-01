#include "String.h"

String::String(const char* str) {
    mSize = strlen(str);
    mStr = new char[mSize + 1];
    strcpy(mStr, str);
}

String::String(char symbol, size_t count) {
    std::string s(count, symbol);
    mSize = s.length();
    mStr = new char[mSize + 1];
    strcpy(mStr, s.c_str());
    mStr[s.length()] = ASCII_NUL;
}

String::String() {
    mSize = 0;
    mStr = new char[1];
    mStr[0] = ASCII_NUL;
}

String::~String() {
    delete [] mStr;
}

String::String(const String& other) {
    mSize = other.getSize();
    mStr = new char[mSize + 1];
    strcpy(mStr, other.toString().c_str());
    mStr[mSize] = ASCII_NUL;
}

void String::swap(String& first, String& second) {
    std::swap(first.mSize, second.mSize);
    std::swap(first.mStr, second.mStr);
}

String& String::operator=(String other) {
    swap(*this, other);
    return *this;
}

std::string String::toString() const {
    return std::string(mStr);
}

size_t String::getSize() const {
    return mSize;
}

void String::append(const char* s) {
    std::string str(s);
    size_t extraSize = strlen(s);
    size_t previousSize = mSize;
    auto * previous = new char[previousSize + 1];
    strcpy(previous, mStr);
    delete [] mStr;
    mStr = new char[previousSize + extraSize + 1];
    std::copy(previous, previous + previousSize, mStr);
    std::copy(str.begin(), str.end(), mStr + previousSize);
    mSize = previousSize + extraSize;
    mStr[mSize] = ASCII_NUL;
    delete [] previous;
}

void String::append(const String& other) {
    append(other.toString().c_str());
}

void String::append(const int& number) {
    char *newStr;
    itoa(number, newStr, NUMBER_SYSTEM);
    append(newStr);
    delete [] newStr;
}

void String::append(const char& c) {
    append(std::string(1, c).c_str());
}

void String::print() const {
    for (int i = 0; i < (int) mSize + 1; ++i) {
        std::cout << static_cast<int>(mStr[i]) << " ";
    }
    std::cout << std::endl;
}

String String::substring(int start, int end) const {
    auto length = static_cast<size_t>(end - start + 1);
    String ans(' ', length);
    for (int i = start; i <= end; i++) {
        ans.mStr[i - start] = mStr[i];
    }
    return ans;
}

String String::postfix(int start) const {
    return substring(start, (int) mSize);
}

String String::suffix(int ending) const {
    return substring(0, ending - 1);
}

char String::charAt(int pos) const {
    return mStr[pos];
}

void String::reverse() {
    std::reverse(mStr, mStr + mSize);
    mStr[mSize] = ASCII_NUL;
}

int String::find(char c) const {
    for(int pos = 0; pos < mSize; ++pos){
        if(mStr[pos] == c) return pos;
    }
    return -1;
}

int String::rfind(char c) const {
    for(size_t pos = 0; pos < mSize; ++pos){
        if(mStr[mSize - pos - 1] == c) return pos;
    }
    return -1;
}

bool String::isDigit() const {
    for(int pos = 0; pos < mSize; ++pos){
        if(mStr[pos] < MIN_ASCII_DIGIT || mStr[pos] > MAX_ASCII_DIGIT) return false;
    }
    return true;
}

bool String::isAlpha() const {
    for(int pos = 0; pos < mSize; ++pos){
        if(mStr[pos] < MIN_ASCII_LOWCACE && mStr[pos] > MAX_ASCII_UPPERCASE || mStr[pos] > MAX_ASCII_LOWCASE || mStr[pos] < MIN_ASCII_UPPERCASE) return false;
    }
    return true;
}

String &String::operator+=(String &other) {
    append(other.toString().c_str());
}
