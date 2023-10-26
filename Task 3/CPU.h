#ifndef ASSIGNMENT2_CPU_H
#define ASSIGNMENT2_CPU_H


#include <ios>
#include <iostream>
#include <memory>

#include "Memory.h"

class CPU : public IMemory {
private:
    int programCounter;
    enum class Operation {
        NONE,
        LOADFROM,
        LOAD,
        STORE,
        MOVE,
        ADDINT,
        ADDFLOAT,
        JUMP = 0x0B,
        HALT = 0x0C
    };
    shared_ptr<Memory> memory;


public:
    CPU(shared_ptr<Memory> &memory, int size = 1e5) : IMemory(size), memory(memory), programCounter(0) {}

    bool execute() {
        /// 1. Fetch
        int firstByte = memory->fetch(programCounter);
        int secondByte = memory->fetch(programCounter + 1);
        programCounter += 2;
        /// 2. Decode
        Operation op = (Operation) (firstByte >> 4);
        int registerAddress = (firstByte & 0x0f);
        /// 3. Execute
        if (op == Operation::LOADFROM) {
            int data = memory->fetch(secondByte);
            this->setAt(registerAddress, data);
        } else if (op == Operation::LOAD) {
            this->setAt(registerAddress, secondByte);
        } else if (op == Operation::STORE) {
            memory->setAt(secondByte, this->fetch(registerAddress));
//            std::cout << hex << "Data: " << uppercase << this->fetch(registerAddress) << endl;
        } else if (op == Operation::MOVE) {
            int firstRegister = (secondByte >> 4);
            int secondRegister = secondByte & 0x0f;
            int dataInFirstRegister = this->fetch(firstRegister);
            this->setAt(secondRegister, dataInFirstRegister);
        } else if (op == Operation::ADDINT) {
            int firstRegister = (secondByte >> 4);
            int secondRegister = secondByte & 0x0f;
            int dataInFirstRegister = this->fetch(firstRegister);
            int dataInSecondRegister = this->fetch(secondRegister);
            this->setAt(registerAddress, dataInFirstRegister + dataInSecondRegister);
        } else if (op == Operation::ADDFLOAT) {
            int firstRegister = (secondByte >> 4);
            int secondRegister = (secondByte & 0x0f);
            double dataInFirstRegister = this->fetch(firstRegister);
            double dataInSecondRegister = this->fetch(secondRegister);
            this->setAt(registerAddress, dataInFirstRegister + dataInSecondRegister);
        } else if (op == Operation::JUMP) {
            int dataInRegister = this->fetch(registerAddress);
            if (dataInRegister == this->fetch(0))
                programCounter = secondByte;
        } else if (op == Operation::HALT) {
            return false;
        }
        return true;
    }

    void setPC(int pos) {
        if (pos > memory->getSize())
            throw out_of_range("Position is out of bound");
        programCounter = pos;
    }
    int getPC() const { return programCounter; }
};


#endif//ASSIGNMENT2_CPU_H
