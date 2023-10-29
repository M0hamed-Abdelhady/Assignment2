#ifndef ASSIGNMENT2_IMEMORY_H
#define ASSIGNMENT2_IMEMORY_H
#include <climits>
#include <memory>
#include <stdexcept>
#include <vector>
using namespace std;
using Byte = unsigned char;
class IMemory {
protected:
    shared_ptr<vector<Byte>> innerMemory;

public:
    explicit IMemory(int size = 0xff + 1) {
        innerMemory = std::make_shared<vector<Byte>>(size);
    }
    virtual ~IMemory() {
        innerMemory->clear();
        innerMemory.reset();
    }
    virtual shared_ptr<vector<Byte>> get() {
        return innerMemory;
    }
    virtual void setAt(int pos, int value) {
        if (value > UCHAR_MAX)
            throw invalid_argument("Value can not fit in one Byte");
        (*innerMemory)[pos] = (Byte) value;
    }
    virtual void setAt(int pos, Byte value) {
        if (value > UCHAR_MAX)
            throw invalid_argument("Value can not fit in one Byte");
        (*innerMemory)[pos] = (Byte) value;
    }
    virtual int fetch(int pos) {
        return (int) (*innerMemory)[pos];
    }
    virtual int getSize() { return (int) innerMemory->size(); }
};

#endif//ASSIGNMENT2_IMEMORY_H
