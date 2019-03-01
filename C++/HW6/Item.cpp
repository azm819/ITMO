#include <afxres.h>
#include "Item.h"

Item::Item() : mType(DEFAULT_TYPE_QUALITY_COST), mCost(DEFAULT_TYPE_QUALITY_COST), mQuality(DEFAULT_TYPE_QUALITY_COST),
               mName(DEFAULT_NAME), mManufacturer(DEFAULT_MANUFACTURER),
               mHeight(DEFAULT_HEIGHT_WIDTH_LENGTH), mWidth(DEFAULT_HEIGHT_WIDTH_LENGTH),
               mLength(DEFAULT_HEIGHT_WIDTH_LENGTH) {}

Item::Item(int type, int cost, int quality, const std::string &name, const std::string &manufacturer, int height,
           int width, int length)
        : mType(abs(type)), mCost(abs(cost)), mQuality(abs(quality) % MAX_QUALITY), mName(name),
          mManufacturer(manufacturer), mHeight(abs(height)), mWidth(abs(width)), mLength(abs(length)) {}

Item::Item(const Item &item) : mType(item.getType()), mCost(item.getCost()), mQuality(item.getQuality()),
                               mName(item.getName()), mManufacturer(item.getManufacturer()),
                               mHeight(item.getHeight()), mWidth(item.getWidth()), mLength(item.getLength()) {}

std::ostream &operator<<(std::ostream &stream, Item &item) {
    stream << "Name:         " << item.getName() << std::endl;
    stream << "Manufacturer: " << item.getManufacturer() << std::endl;
    stream << "Type:         " << item.getType() << std::endl;
    stream << "Cost:         " << item.getCost() << std::endl;
    stream << "Quality:      " << item.getQuality() << std::endl;
    stream << "Height:       " << item.getHeight() << std::endl;
    stream << "Width:        " << item.getWidth() << std::endl;
    stream << "Length:       " << item.getLength() << std::endl;
    stream << "Valume:       " << item.getValume() << std::endl;
    return stream;
}

std::string Item::getName() const {
    return mName;
}

std::string Item::getManufacturer() const {
    return mManufacturer;
}

int Item::getQuality() const {
    return mQuality;
}

int Item::getCost() const {
    return mCost;
}

int Item::getType() const {
    return mType;
}

int Item::getHeight() const {
    return mHeight;
}

int Item::getWidth() const {
    return mWidth;
}

int Item::getLength() const {
    return mLength;
}

int Item::getNextAbs(int n) const {
    int res = 1;
    while (res <= n) {
        res *= SYSTEM_VALUE;
    }
    return res;
}

void Item::makeBetter() {
    mQuality = MAX_QUALITY;
}

void Item::makeWorse() {
    mQuality = MIN_QUALITY;
}

int Item::getValume() const {
    return mHeight * mWidth * mLength;
}

bool Item::isQualitative() const {
    return mQuality >= AVERAGE_QUALITY;
}

Item &Item::operator=(const Item &item) {
    mName = item.getName();
    mCost = item.getCost();
    mType = item.getType();
    mManufacturer = item.getManufacturer();
    mQuality = item.getQuality();
    return *this;
}

Item Item::operator+(const Item &item) {
    std::string newName = item.getName().size() > mName.size() ? item.getName() : mName;
    std::string newManufacturer =
            item.getManufacturer().size() > mManufacturer.size() ? item.getManufacturer() : mManufacturer;
    int newType = std::max(mType, item.getType());
    int newQuality = std::max(mQuality, item.getQuality());
    int newCost = std::max(mCost, item.getCost());
    int newHeight = std::max(mHeight, item.getHeight());
    int newWidth = std::max(mWidth, item.getWidth());
    int newLength = std::max(mLength, item.getLength());
    return Item(newType, newCost, newQuality, newName, newManufacturer, newHeight, newWidth, newLength);
}

Item Item::operator-(const Item &item) {
    std::string newName = item.getName().size() < mName.size() ? item.getName() : mName;
    std::string newManufacturer =
            item.getManufacturer().size() < mManufacturer.size() ? item.getManufacturer() : mManufacturer;
    int newType = std::min(mType, item.getType());
    int newQuality = std::min(mQuality, item.getQuality());
    int newCost = std::min(mCost, item.getCost());
    int newHeight = std::min(mHeight, item.getHeight());
    int newWidth = std::min(mWidth, item.getWidth());
    int newLength = std::min(mLength, item.getLength());
    return Item(newType, newCost, newQuality, newName, newManufacturer, newHeight, newWidth, newLength);
}

Item Item::operator+() {
    Item Item(*this);
    Item.makeBetter();
    return Item;
}

Item Item::operator-() {
    Item Item(*this);
    Item.makeWorse();
    return Item;
}

Item Item::operator*(const Item &item) {
    std::string newName =
            item.getName().size() > mName.size() ? item.getName() + " and " + mName : mName + " and " + item.getName();
    std::string newManufacturer =
            item.getManufacturer().size() > mManufacturer.size() ? item.getManufacturer() + " and " + mManufacturer :
            mManufacturer + " and " + item.getManufacturer();
    int newType = mType + item.getType();
    int newQuality = (mQuality + item.getQuality()) % MAX_QUALITY;
    int newCost = mCost + item.getCost();
    int newHeight = mHeight + item.getHeight();
    int newWidth = mWidth + item.getWidth();
    int newLength = mLength + item.getLength();
    return Item(newType, newCost, newQuality, newName, newManufacturer, newHeight, newWidth, newLength);
}

Item Item::operator/(const Item &item) {
    std::string newName =
            item.getName().size() < mName.size() ? item.getName() + " and " + mName : mName + " and " + item.getName();
    std::string newManufacturer =
            item.getManufacturer().size() < mManufacturer.size() ? item.getManufacturer() + " and " + mManufacturer :
            mManufacturer + " and " + item.getManufacturer();
    int newType = abs(mType - item.getType());
    int newQuality = abs(mQuality - item.getQuality()) % MAX_QUALITY;
    int newCost = abs(mCost - item.getCost());
    int newHeight = mHeight - item.getHeight();
    int newWidth = mWidth - item.getWidth();
    int newLength = mLength - item.getLength();
    return Item(newType, newCost, newQuality, newName, newManufacturer, newHeight, newWidth, newLength);
}

Item Item::operator%(const Item &item) {
    int newType = mType % item.getType();
    int newQuality = mQuality % item.getQuality();
    int newCost = mCost % item.getCost();
    int newHeight = mHeight % item.getHeight();
    int newWidth = mWidth % item.getWidth();
    int newLength = mLength % item.getLength();
    return Item(newType, newCost, newQuality, mName, mManufacturer, newHeight, newWidth, newLength);
}

Item &Item::operator++() {
    mQuality++;
    mCost += AVERAGE_COST;
    return *this;
}

Item &Item::operator--() {
    mQuality--;
    mCost -= AVERAGE_COST;
    return *this;
}

Item Item::operator++(int) {
    Item item = Item(*this);
    ++*this;
    return item;
}

Item Item::operator--(int) {
    Item item = Item(*this);
    --*this;
    return item;
}

bool Item::operator==(const Item &item) const {
    return !(mQuality != item.getQuality() || mLength != item.getLength() || mCost != item.getCost() ||
             mWidth != item.getWidth() || mHeight != item.getHeight() || mType != item.getType());
}

bool Item::operator!=(const Item &item) const {
    return !(mQuality == item.getQuality() || mLength == item.getLength() || mCost == item.getCost() ||
             mWidth == item.getWidth() || mHeight == item.getHeight() || mType == item.getType());
}

bool Item::operator<(const Item &item) const {
    return getValume() < item.getValume();
}

bool Item::operator>(const Item &item) const {
    return getValume() > item.getValume();
}

bool Item::operator<=(const Item &item) const {
    return getValume() <= item.getValume();
}

bool Item::operator>=(const Item &item) const {
    return getValume() >= item.getValume();
}

bool Item::operator!() const {
    return isQualitative();
}

bool Item::operator&&(const Item &item) const {
    return isQualitative() && item.isQualitative();
}

bool Item::operator||(const Item &item) const {
    return isQualitative() || item.isQualitative();
}

Item Item::operator~() {
    int newType = getNextAbs(mType) - mType;
    int newQuality = getNextAbs(mQuality) - mQuality;
    int newCost = getNextAbs(mCost) - mCost;
    int newHeight = getNextAbs(mHeight) - mHeight;
    int newWidth = getNextAbs(mWidth) - mWidth;
    int newLength = getNextAbs(mLength) - mLength;
    return Item(newType, newCost, newQuality, mName, mManufacturer, newHeight, newWidth, newLength);
}

Item Item::operator&(const Item &item) {
    int newType = mType & item.getType();
    int newQuality = mQuality & item.getQuality();
    int newCost = mCost & item.getCost();
    int newHeight = mHeight & item.getHeight();
    int newWidth = mWidth & item.getWidth();
    int newLength = mLength & item.getLength();
    return Item(newType, newCost, newQuality, mName, mManufacturer, newHeight, newWidth, newLength);
}

Item Item::operator|(const Item &item) {
    int newType = mType | item.getType();
    int newQuality = mQuality | item.getQuality();
    int newCost = mCost | item.getCost();
    int newHeight = mHeight | item.getHeight();
    int newWidth = mWidth | item.getWidth();
    int newLength = mLength | item.getLength();
    return Item(newType, newCost, newQuality, mName, mManufacturer, newHeight, newWidth, newLength);
}

Item Item::operator^(const Item &item) {
    int newType = mType ^item.getType();
    int newQuality = mQuality ^item.getQuality();
    int newCost = mCost ^item.getCost();
    int newHeight = mHeight ^item.getHeight();
    int newWidth = mWidth ^item.getWidth();
    int newLength = mLength ^item.getLength();
    return Item(newType, newCost, newQuality, mName, mManufacturer, newHeight, newWidth, newLength);
}

Item Item::operator<<(int n) {
    return Item(mType, mCost << n, mQuality, mName, mManufacturer, mHeight, mWidth, mLength);
}

Item Item::operator>>(int n) {
    return Item(mType, mCost >> n, mQuality, mName, mManufacturer, mHeight, mWidth, mLength);
}

Item &Item::operator+=(const Item &item) {
    *this = *this + item;
    return *this;
}

Item &Item::operator-=(const Item &item) {
    *this = *this - item;
    return *this;
}

Item &Item::operator*=(const Item &item) {
    *this = *this * item;
    return *this;
}

Item &Item::operator/=(const Item &item) {
    *this = *this / item;
    return *this;
}

Item &Item::operator%=(const Item &item) {
    *this = *this % item;
    return *this;
}

Item &Item::operator&=(const Item &item) {
    *this = *this & item;
    return *this;
}

Item &Item::operator|=(const Item &item) {
    *this = *this | item;
    return *this;
}

Item &Item::operator^=(const Item &item) {
    *this = *this ^ item;
    return *this;
}

Item &Item::operator<<=(int n) {
    *this = *this << n;
    return *this;
}

Item &Item::operator>>=(int n) {
    *this = *this >> n;
    return *this;
}

bool Item::operator[](const int valume) const {
    return getValume() <= valume;
}

Item &Item::operator,(Item &item) const {
    return item;
}

Item::operator std::string() const {
    return "It's " + mName + " from " + mManufacturer;
}

Item::operator bool() const {
    return isQualitative();
}

Item &Item::operator->*(Item &) {
    return *this;
}

Item Item::operator()(const Item &first, const Item &second) const {
    return second;
}

std::string Item::operator->() {
    return getManufacturer();
}


