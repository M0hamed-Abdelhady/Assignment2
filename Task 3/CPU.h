#ifndef ASSIGNMENT2_CPU_H
#define ASSIGNMENT2_CPU_H


#include <iomanip>
#include <ios>
#include <iostream>
#include <memory>
#include <sstream>

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
            unsigned int exponent : 3;// Exp in Excess 4 Notation
            unsigned int sign : 1;

        } raw;
    } myFloat;
    shared_ptr<Memory> memory;


public:
    explicit CPU(shared_ptr<Memory> &memory, int size = 0XF + 1) : IMemory(size), memory(memory), programCounter(0) {}

    pair<int, int> fetchTwoBytes() {
        return {memory->fetch(programCounter++), memory->fetch(programCounter++)};
    }

    pair<Operation, int> decode(int &firstByte) {
        return {(Operation) (firstByte >> 4), firstByte & 0x0f};
    }

    string decodeMessage(int &firstByte, int &secondByte, Operation &op, int &registerAddress) {
        stringstream s;
        if (op == Operation::LOADFROM) {
            s << "LOAD the register « " << hex << uppercase << setw(2) << setfill('0') << registerAddress
              << " » with the bit pattern found in the memory cell whose address is « "
              << setw(2) << setfill('0') << secondByte << " » With this data";
        } else if (op == Operation::LOAD) {
            s << "LOAD the register « " << hex << uppercase << setw(2) << setfill('0') << registerAddress
              << " » with the bit pattern « " << setw(2) << setfill('0') << secondByte << " »";
        } else if (op == Operation::STORE) {
            s << "STORE the bit pattern found in register « " << hex
              << uppercase << setw(2) << setfill('0') << registerAddress << " » in the memory cell whose address is « " << setw(2) << setfill('0') << secondByte << " »";
        } else if (op == Operation::MOVE) {
            int firstRegister = (secondByte >> 4);
            int secondRegister = secondByte & 0x0f;
            s << "MOVE the bit pattern found in register « " << hex
              << uppercase << setw(2) << setfill('0') << firstRegister << " »  to register « " << setw(2) << setfill('0') << secondRegister << " »";
        } else if (op == Operation::ADDINT) {
            int firstRegister = (secondByte >> 4);
            int secondRegister = secondByte & 0x0f;
            s << "ADD the bit patterns in registers « " << hex << uppercase << setw(2) << setfill('0') << firstRegister << " »  and « " << setw(2) << setfill('0') << secondRegister
              << " » as though they were ▬ two’s complement representations ▬ and leave the result in register « " << setw(2) << setfill('0') << registerAddress << " »";
        } else if (op == Operation::ADDFLOAT) {
            int firstRegister = (secondByte >> 4);
            int secondRegister = (secondByte & 0x0f);
            s << "ADD the bit patterns in registers « " << hex << uppercase << setw(2) << setfill('0') << firstRegister << " »  and « " << setw(2) << setfill('0') << secondRegister
              << " » as though they were ▬ floating-point notation ▬ and leave the result in register « " << setw(2) << setfill('0') << registerAddress << " »";
        } else if (op == Operation::JUMP) {
            s << "JUMP to the instruction located in the memory cell at address « " << hex
              << uppercase << setw(2) << setfill('0') << secondByte << " » if the bit pattern in register « " << setw(2) << setfill('0') << registerAddress << " » is equal to the bit pattern in register number « 0 »";
        } else if (op == Operation::HALT) {
            s << "HALT execution";
        }
        return s.str();
    }

    bool execute(int &firstByte, int &secondByte, Operation &op, int &registerAddress) {
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
            this->setAt(registerAddress, (Byte) (f1.integer + f2.integer));
        } else if (op == Operation::JUMP) {
            int dataInRegister = this->fetch(registerAddress);
            if (dataInRegister == this->fetch(0))
                programCounter = secondByte;
        } else if (op == Operation::HALT) {
            return 0;
        }
        return 1;
    }

    string runCycle() {
        /// 1. Fetch
        auto [firstByte, secondByte] = fetchTwoBytes();
        /// 2. Decode
        auto [op, registerAddress] = decode(firstByte);
        string ret = decodeMessage(firstByte, secondByte, op, registerAddress);
        /// 3. Execute
        if (execute(firstByte, secondByte, op, registerAddress))
            return ret;
        else {
            cout << ret << endl;
            exit(0);
        }
    }

    void setPC(int pos) {
        if (pos > memory->getSize())
            throw out_of_range("Position is out of bound");
        programCounter = pos;
    }

    int getPC() const { return programCounter; }
};


#endif//ASSIGNMENT2_CPU_H
