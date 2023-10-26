//
// Created by andro on 10/26/2023.
//

#ifndef ASSIGNMENT2_MEMORY_H
#define ASSIGNMENT2_MEMORY_H

#include "IMemory.h"
#include <fstream>

class Memory : public IMemory {

public:
    void read(ifstream &file) {
        int x;
        int ptr = 0;

        while (file >> hex >> x) {
            int firstByte = (x & 0xff00) >> 8;
            int secondByte = x & 0x00ff;
            this->setAt(ptr, firstByte);
            this->setAt(ptr + 1, secondByte);
            ptr += 2;
        }
    }
};


#endif//ASSIGNMENT2_MEMORY_H
