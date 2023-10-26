// File: A2_S8_20220008_7.cpp
// Purpose: Solving Problem no. 7
// Author: Ahmed Osama Fathy.
// Section: S8
// ID: 20220008
// TA: Khaled Ahmed
// Date: 26 Oct 2023
#include <iostream>
#include <vector>
struct dominoT {
    int leftDots;
    int rightDots;
    dominoT(int l, int r) : leftDots(l), rightDots(r) {}
    std::string toString() const {
        return (std::to_string(leftDots) + "|" + std::to_string(rightDots));
    }
};

std::vector<dominoT> path;
bool FormsDominoChain(std::vector<dominoT> &dominos, std::string &mask, int last = -1) {
    bool ret = false;
    if (mask.find('0') == std::string::npos) {
        std::cout << "Found Path:\n";
        for (dominoT &domino: path)
            std::cout << domino.toString() << (&domino != &path.back() ? " - " : " ");
        std::cout << std::endl;
        return true;
    }
    for (int i = 0; i < dominos.size(); ++i) {
        if (mask[i] == '0' && (last == dominos[i].leftDots || last == -1)) {
            mask[i] = '1';
            path.emplace_back(dominos[i]);
            ret = std::max(ret, FormsDominoChain(dominos, mask, dominos[i].rightDots));
            path.pop_back();
            mask[i] = '0';
        }
    }
    return ret;
}

int main() {
    /// Example 1
    std::vector<dominoT> dominoSet{{1, 4}, {2, 6}, {4, 4}, {6, 1}, {4, 3}};
    std::string msk(dominoSet.size(), '0');
    FormsDominoChain(dominoSet, msk);

    /// Example 2
    dominoSet.emplace_back(3, 4);
    path.clear();
    msk = std::string(dominoSet.size(), '0');
    FormsDominoChain(dominoSet, msk);
}
