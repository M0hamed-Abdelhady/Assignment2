// File: A2_S8_20220008_9.cpp
// Purpose: Solving Problem no. 9
// Author: Mohamed Tamer Mohamed.
// Section: S8
// ID: 20220514
// TA: Khaled Ahmed
// Date: 26 Oct 2023

#include <iostream>
#include <map>

using namespace std;

class bearGame {
public:

    static bool bears(int n) {
        // Post condition: A true return value means it is possible to win
        // the bear game by starting with n bears. A false value means that
        // it is not possible to win the bear game starting with n bears.
        // Examples:
        // bear(250) is true (as shown above)
        // bear(42) is true
        // bear(84) is true
        // bear(53) is false
        // bear(41) is false
        if (n == 42)
            return 1;
        if (n < 42)
            return 0;

        bool ret = 0;
        if (n % 2 == 0)
            ret |= bears(n / 2);
        if (n % 3 == 0 || n % 4 == 0) {
            int firstDigit = n % 10;
            int secondDigit = (n / 10) % 10;
            if (firstDigit * secondDigit > 0)
                ret |= bears(n - firstDigit * secondDigit);
        }
        if (n % 5 == 0)
            ret |= bears(n - 42);
        return ret;
    }

};

int main() {
    cout << bearGame::bears(250) << endl;
    cout << bearGame::bears(42) << endl;
    cout << bearGame::bears(84) << endl;
    cout << bearGame::bears(53) << endl;
    cout << bearGame::bears(41) << endl;
}

