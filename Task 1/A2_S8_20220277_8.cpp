/*
    File: A2_S8_20220277_8.cpp
    Purpose: Solving Problem 8
    Author: Mohamed Ahmed Abdelhady
    Section: S8
    ID: 20220277
    TA: Khaled Ahmed
    Date: 26 Oct 2023
*/
#include <iostream>
#include <cmath>

using namespace std;

void print(int n, int i) {
    if (n == 1) {
        for (int j = 0; j < i; ++j) cout << ' ';
        return void(cout << "*\n");
    }
    print(n / 2, i);
    for (int j = 0; j < i; ++j) cout << ' ';
    for (int j = 0; j < n; ++j) cout << "* ";
    cout << '\n';
    print(n / 2, i + n);
}

int inputScale() {
    cout << "Input Pattern Scale (must be power of 2):";
    int scale;
    while (true) {
        cin >> scale;
        if (cin.fail() || log2(scale) != int(log2(scale))) {
            cout << "please input a valid scale:";
            continue;
        }
        return scale;
    }
}

int inputStart() {
    cout << "Input Starting Column:";
    int start;
    while (true) {
        cin >> start;
        if (cin.fail() || start < 0) {
            cout << "please input a valid start column:";
            continue;
        }
        return start;
    }
}

int main() {
    print(inputScale(), inputStart());
    return 0;
}