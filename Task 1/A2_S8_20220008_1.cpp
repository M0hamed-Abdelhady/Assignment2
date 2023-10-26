// File: A2_S8_20220008_1.cpp
// Purpose: Solving Problem no. 1
// Author: Ahmed Osama Fathy.
// Section: S8
// ID: 20220008
// TA: Khaled Ahmed
// Date: 26 Oct 2023
#include <iostream>

int main() {
    std::string s, formatted;
    std::getline(std::cin, s);
    for (int i = 0; i < s.size(); ++i) {
        if (s[i] != ' ') formatted += tolower(s[i]);
        else {
            formatted += ' ';
            for (; i < s.size() && s[i] == ' '; ++i);
            --i;
        }
    }
    formatted[0] = toupper(formatted[0]);
    std::cout << formatted << std::endl;
    return 0;
}
