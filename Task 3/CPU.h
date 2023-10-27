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
    typedef union {
        uint8_t integer;
        struct
        {
            /*
             * Order is important.
             * Here the members of the union data structure use the same memory (8 bits).
             * The ordering is taken
             * from the LSB to the MSB.
             */
            unsigned int mantissa : 4;
            unsigned int exponent : 3; // Exp in Excess 4 Notation
            unsigned int sign : 1;

        } raw;
    } myFloat;

    shared_ptr<Memory> memory;


public:
    explicit CPU(shared_ptr<Memory> &memory, int size = 1e5) : IMemory(size), memory(memory), programCounter(0) {}

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
            if (secondByte == 0)
                std::cout << hex << "Data: " << uppercase << this->fetch(registerAddress) << dec << endl;
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
            Byte dataInFirstRegister = this->fetch(firstRegister);
            Byte dataInSecondRegister = this->fetch(secondRegister);
            myFloat f1, f2;
            f1.raw.sign = dataInFirstRegister >> 7;
            f1.raw.exponent = (dataInFirstRegister & 0b01110000) >> 4;
            f1.raw.mantissa = (dataInFirstRegister & 0b00001111);
            f2.raw.sign = dataInSecondRegister >> 7;
            f2.raw.exponent = (dataInSecondRegister & 0b01110000) >> 4;
            f2.raw.mantissa = (dataInSecondRegister & 0b00001111);
            this->setAt(registerAddress, (Byte)(f1.integer + f2.integer));
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
