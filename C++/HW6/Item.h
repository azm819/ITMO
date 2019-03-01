#pragma once

#include <iostream>
#include <string>

class Item {
public:
    Item();
    explicit Item(int type, int cost, int quality, const std::string &name, const std::string &manufacturer, int height, int width, int length);
    Item(const Item &item);

    friend std::ostream &operator<<(std::ostream &stream, Item &item);
    Item &operator=(const Item &item);
    Item operator+(const Item &item);
    Item operator-(const Item &item);
    Item operator+();
    Item operator-();
    Item operator*(const Item &item);
    Item operator/(const Item &item);
    Item operator%(const Item &item);
    Item &operator++();//префикс
    Item &operator--();
    Item operator++(int);//суффикс
    Item operator--(int);
    bool operator==(const Item &item) const;
    bool operator!=(const Item &item) const;
    bool operator>(const Item &item) const;
    bool operator<(const Item &item) const;
    bool operator>=(const Item &item) const;
    bool operator<=(const Item &item) const;
    bool operator!() const;
    bool operator&&(const Item &item) const;
    bool operator||(const Item &item) const;
    Item operator~();
    Item operator&(const Item &item);
    Item operator|(const Item &item);
    Item operator^(const Item &item);
    Item operator<<(int n);
    Item operator>>(int n);
    Item &operator+=(const Item &item);
    Item &operator-=(const Item &item);
    Item &operator*=(const Item &item);
    Item &operator/=(const Item &item);
    Item &operator%=(const Item &item);
    Item &operator&=(const Item &item);
    Item &operator|=(const Item &item);
    Item &operator^=(const Item &item);
    Item &operator<<=(int n);
    Item &operator>>=(int n);
    bool operator[](int valume) const;
    Item &operator,(Item &item) const;
    explicit operator std::string() const;
    explicit operator bool() const;
    std::string operator->();
    Item &operator->*(Item &);
    Item operator()(const Item &first, const Item &second) const;

    std::string getName() const;
    std::string getManufacturer() const;
    int getType() const;
    int getCost() const;
    int getQuality() const;
    int getHeight() const;
    int getWidth() const;
    int getLength() const;
    int getValume() const;
    bool isQualitative() const;

private:
    const int DEFAULT_TYPE_QUALITY_COST = 0;
    const int DEFAULT_HEIGHT_WIDTH_LENGTH = 0;
    const std::string DEFAULT_NAME = "Car";
    const std::string DEFAULT_MANUFACTURER = "Germany";
    const int MAX_QUALITY = 10;
    const int MIN_QUALITY = 0;
    const int SYSTEM_VALUE = 10;
    const int AVERAGE_COST = 10;
    const int AVERAGE_QUALITY = 5;

    int mType;
    int mCost;
    int mQuality;
    int mHeight;
    int mWidth;
    int mLength;
    std::string mName;
    std::string mManufacturer;

    int getNextAbs(int n) const;

    void makeBetter();

    void makeWorse();
};
