#include "BigReal.h"

bool BigReal::isValidReal(string realNumber) {
    int start = 0;
    sign = (realNumber.front() == '-' ? 1 : 0);
    if (realNumber.front() == '+' || realNumber.front() == '-')
        start++;
    bool foundDot = 0;
    integerPart = "";
    floatingPart = "";
    for (int i = start; i < realNumber.size(); i++) {
        if (realNumber[i] == '.')
            if (foundDot)
                return 0;
            else
                foundDot = 1;
        else if (isdigit(realNumber[i]))
            if (foundDot)
                floatingPart += realNumber[i];
            else
                integerPart += realNumber[i];
        else
            return 0;
    }
    if (integerPart.empty())
        integerPart = "0";
    if (floatingPart.empty())
        floatingPart = "0";
    this->realNumber = (sign ? "-" : "") + integerPart + "." + floatingPart;
    return 1;
}

void BigReal::checkValidation(string realNumber) {
    if (!isValidReal(realNumber)) {
        cout << "Not a valid real number." << endl;
        sign = 0;
        realNumber = "0.0";
        integerPart = "0";
        floatingPart = "0";
    }
}

BigReal::BigReal(double realNumber) {
    string real = to_string(realNumber);
    while (real.back() == '0')
        real.pop_back();
    isValidReal(real);
}

BigReal::BigReal(string realNumber) {
    checkValidation(realNumber);
}

BigReal::BigReal(const BigReal &other) {
    this->realNumber = other.realNumber;
    this->floatingPart = other.floatingPart;
    this->integerPart = other.integerPart;
    this->sign = other.sign;
}

void BigReal::operator=(BigReal other) {
    this->realNumber = other.realNumber;
    this->floatingPart = other.floatingPart;
    this->integerPart = other.integerPart;
    this->sign = other.sign;
}

void BigReal::setNumber(string realNumber) {
    checkValidation(realNumber);
}

BigReal BigReal::operator+(BigReal other) {
    // make the operator applied only when a + b or -(a + b)
    if (other.sign != this->sign)
        if (other.sign) {
            other.sign = 0;
            auto ret = *this - other;
            other.sign = 1;
            return ret;
        } else {
            this->sign = 0;
            auto ret = other - *this;
            this->sign = 1;
            return ret;
        }

    BigReal ret(0);
    ret.sign = this->sign;

    int maxFloatingSize = max(other.floatingPart.size(), this->floatingPart.size());
    ret.floatingPart.resize(maxFloatingSize);
    bool carry = 0;

    for (int i = maxFloatingSize - 1; i >= 0; i--) {
        int digit = 0;
        if (i < this->floatingPart.size())
            digit += this->floatingPart[i] - '0';
        if (i < other.floatingPart.size())
            digit += other.floatingPart[i] - '0';
        digit += carry;
        if (digit >= 10)
            digit -= 10, carry = 1;
        else
            carry = 0;
        ret.floatingPart[i] = char(digit + '0');
    }

    int maxIntegerSize = max(other.integerPart.size(), this->integerPart.size());
    ret.integerPart.resize(maxIntegerSize);

    reverse(this->integerPart.begin(), this->integerPart.end());
    reverse(other.integerPart.begin(), other.integerPart.end());
    for (int i = 0; i < maxIntegerSize; i++) {
        int digit = 0;
        if (i < this->integerPart.size())
            digit += this->integerPart[i] - '0';
        if (i < other.integerPart.size())
            digit += other.integerPart[i] - '0';
        digit += carry;
        if (digit >= 10)
            digit -= 10, carry = 1;
        else
            carry = 0;
        ret.integerPart[i] = char(digit + '0');
    }

    reverse(this->integerPart.begin(), this->integerPart.end());
    reverse(other.integerPart.begin(), other.integerPart.end());
    if (carry)
        ret.integerPart.push_back('1');
    reverse(ret.integerPart.begin(), ret.integerPart.end());
    ret.realNumber = (ret.sign ? "-" : "") + ret.integerPart + "." + ret.floatingPart;

    return ret;
}

BigReal BigReal::operator-(BigReal other) {
    // make the operator applied when +a - +b only
    if (other.sign) {
        other.sign = 0;
        BigReal ret(0);
        if (this->sign) {
            this->sign = 0;
            ret = other - *this;
            this->sign = 1;
        } else
            ret = other + *this;
        other.sign = 1;
        return ret;
    }

    if (this->sign) {
        other.sign = 1;
        auto ret = *this + other;
        other.sign = 0;
        return ret;
    }
    if (other > *this) {
        auto ret = other - *this;
        ret.sign = 1;
        ret.realNumber.insert(0, "-");
        return ret;
    }

    BigReal ret(0);
    ret.sign = 0;

    int maxFloatingSize = max(other.floatingPart.size(), this->floatingPart.size());
    ret.floatingPart.resize(maxFloatingSize);
    bool carry = 0;

    for (int i = maxFloatingSize - 1; i >= 0; i--) {
        int digit = 0;
        if (i < this->floatingPart.size())
            digit += this->floatingPart[i] - '0';
        if (i < other.floatingPart.size())
            digit -= other.floatingPart[i] - '0';
        digit -= carry;
        if (digit < 0)
            digit += 10, carry = 1;
        else
            carry = 0;
        ret.floatingPart[i] = char(digit + '0');
    }

    int maxIntegerSize = max(other.integerPart.size(), this->integerPart.size());
    ret.integerPart.resize(maxIntegerSize);

    reverse(this->integerPart.begin(), this->integerPart.end());
    reverse(other.integerPart.begin(), other.integerPart.end());
    for (int i = 0; i < maxIntegerSize; i++) {
        int digit = 0;
        if (i < this->integerPart.size())
            digit += this->integerPart[i] - '0';
        if (i < other.integerPart.size())
            digit -= other.integerPart[i] - '0';
        digit -= carry;
        if (digit < 0)
            digit += 10, carry = 1;
        else
            carry = 0;
        ret.integerPart[i] = char(digit + '0');
    }

    reverse(this->integerPart.begin(), this->integerPart.end());
    reverse(other.integerPart.begin(), other.integerPart.end());

    reverse(ret.integerPart.begin(), ret.integerPart.end());

    while (!ret.integerPart.empty() && ret.integerPart.back() == '0')
        ret.integerPart.pop_back();
    if (ret.integerPart.empty())
        ret.integerPart.push_back('0');

    while (!ret.floatingPart.empty() && ret.floatingPart.back() == '0')
        ret.floatingPart.pop_back();
    if (ret.floatingPart.empty())
        ret.floatingPart.push_back('0');

    ret.realNumber = (ret.sign ? "-" : "") + ret.integerPart + "." + ret.floatingPart;

    return ret;
}

bool BigReal::operator<(BigReal &other) {
    // check if integer part has more digits or less digits
    if (this->integerPart.size() < other.integerPart.size())
        return 1;
    if (this->integerPart.size() > other.integerPart.size())
        return 0;
    // if the size is equal
    // loop over the integer part from the leftmost digit and check if it is bigger
    for (int i = 0; i < this->integerPart.size(); i++) {
        if (this->integerPart[i] < other.integerPart[i])
            return 1;
        if (this->integerPart[i] > other.integerPart[i])
            return 0;
    }
    // if the integer part is equal
    // loop over the floating part from the leftmost digit and check if it is bigger
    for (int i = 0; i < min(this->floatingPart.size(), other.floatingPart.size()); i++) {
        if (this->floatingPart.size() < other.floatingPart.size())
            return 1;
        if (this->floatingPart.size() > other.floatingPart.size())
            return 0;
    }
    // if both are equal to the minimum size of both check who has the bigger size
    return this->floatingPart.size() < other.floatingPart.size();
}

bool BigReal::operator>(BigReal &other) {
    return other < *this;
}

bool BigReal::operator==(BigReal &other) {
    return this->realNumber == other.realNumber;
}

ostream &operator<<(ostream &out, BigReal num) {
    cout << num.realNumber;
    return out;
}









