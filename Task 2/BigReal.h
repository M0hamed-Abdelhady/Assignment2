//
// Created by mohamed tamer on 26-Oct-23.
//

#ifndef ASSIGNMENT2_BIGREAL_H
#define ASSIGNMENT2_BIGREAL_H

#include <iostream>
#include <string>
#include <algorithm>

using namespace std;
const double epsilon = 1e-9;

class BigReal {
private:
    bool sign; // true for negative and false for positive
    string integerPart; // represents the integer part of the real number
    string floatingPart; // represents the floating part of the real number
    string realNumber; // represents the whole real number
    bool isValidReal(string realNumber); // returns True if correct real and assigns all the member variables
public:
    void checkValidation(string realNumber); // throws an error message if invalid real number
    BigReal(double realNumber = 0.0); // Default constructor
    BigReal(string realNumber); // Initialize from string
    BigReal(const BigReal &other); // Copy constructor
    void setNumber(string realNumber);

    void operator=(BigReal other); // Assignment operator

    BigReal operator+(BigReal other);

    BigReal operator-(BigReal other);

    bool operator<(BigReal &other);

    bool operator>(BigReal &other);

    bool operator==(BigReal &other);

    friend ostream &operator<<(ostream &out, BigReal num);

};


#endif //ASSIGNMENT2_BIGREAL_H
