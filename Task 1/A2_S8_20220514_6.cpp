// File: A2_S8_20220008_6.cpp
// Purpose: Solving Problem no. 6
// Author: Mohamed Tamer Mohamed.
// Section: S8
// ID: 20220514
// TA: Khaled Ahmed
// Date: 26 Oct 2023

#include <iostream>
#include <string>

using namespace std;

class print {
public:
    inline static string binaryNumber = "";
    inline static string number = "";

    static void getBinary(int n) {
        if (n == 0)
            return;
        if (n & 1)
            binaryNumber += '1';
        else
            binaryNumber += '0';

        getBinary(n / 2);
    }

    static void binaryPrint(int n) {
        binaryNumber = "";
        getBinary(n);
        if (n == 0)
            binaryNumber = "0";
        for (int i = 0; i < binaryNumber.size() / 2; i++)
            swap(binaryNumber[i], binaryNumber[(int) binaryNumber.size() - i - 1]);
        cout << binaryNumber << endl;
    }

    static void generateSuffix(int k) {
        if (k == 0)
            return void(cout << number << endl);
        for (char bit = '0'; bit <= '1'; bit++) {
            number += bit;
            generateSuffix(k - 1);
            number.pop_back();
        }
    }

    static void numbers(string prefix, int k) {
        number = prefix;
        generateSuffix(k);
    };
};


int main() {
    print::binaryPrint(0);
    print::binaryPrint(4);
    print::binaryPrint(27);
    cout << endl;
    print::numbers("00101", 2);
    return 0;
}
