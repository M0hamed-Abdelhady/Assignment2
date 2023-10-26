#include <iostream>
#include <vector>
struct dominoT {
    int leftDots;
    int rightDots;
    dominoT(int l,int r):leftDots(l),rightDots(r){}
};

bool FormsDominoChain(std::vector<dominoT>& dominos) {

}

int main() {
    std::vector<dominoT> dominos;
    dominos.emplace_back(1,4);
    dominos.emplace_back(2,6);
    dominos.emplace_back(4,4);
    dominos.emplace_back(6,1);
    dominos.emplace_back(4,3);
}
