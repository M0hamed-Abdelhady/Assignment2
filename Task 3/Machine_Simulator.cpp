#include "CPU.h"
#include "Memory.h"
#include <fstream>
#include <iostream>


int main() {
    ifstream fin("instructions.txt");
    shared_ptr<Memory> memo = shared_ptr<Memory>(new Memory());
    memo->read(fin);
    CPU myCpu(memo);
    while (myCpu.execute()) {
        cout << myCpu.getPC() << " \n";
    }
}