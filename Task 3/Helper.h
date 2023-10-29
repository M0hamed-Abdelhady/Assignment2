#include "CPU.h"
#include <iomanip>
#include <limits>
#include <string>
#include <vector>
using namespace std;
namespace Helper {

    int RunMenu(vector<string> &menu, const string &Title = "") {
        cout << "┌ " << Title << "\n";
        for (int i = 0; i < menu.size(); ++i) {
            cout << "├─ " << i + 1 << ". " << menu[i] << endl;
        }
        cout << "└ » ";
        int choice;
        cin >> choice;
        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            throw std::runtime_error("Input must be integer");
        }
        if (choice > menu.size() || choice < 1)
            throw std::out_of_range("Your Choice is out of range");
        return choice;
    }

    void showPC(CPU &cpu) {
        cout << "Program Counter " << hex << setw(2) << setfill('0') << uppercase << cpu.getPC() << endl;
    }

    void showRegister(IMemory &cpu) {
        cout << " Address\tHex\n";
        for (int i = 0; i < cpu.getSize(); ++i) {
            cout << "►  " << hex << setw(2) << setfill('0') << uppercase << i
                 << setw(12) << setfill(' ') << " " << setw(2) << setfill('0') << cpu.fetch(i) << endl;
        }
    }
    void showMemory(IMemory &memo) {
        cout << " Address\tHex\t Address\tHex\t Address\tHex\n";
        for (int i = 0; i + 2 < memo.getSize(); i += 3) {
            cout << "►  " << hex << setw(2) << setfill('0') << uppercase << i
                 << setw(12) << setfill(' ') << " " << setw(2) << setfill('0') << memo.fetch(i)
                 << "\t►  " << hex << setw(2) << setfill('0') << uppercase << (i + 1)
                 << setw(12) << setfill(' ') << " " << setw(2) << setfill('0') << memo.fetch((i + 1))
                 << "\t►  " << hex << setw(2) << setfill('0') << uppercase << (i + 2)
                 << setw(12) << setfill(' ') << " " << setw(2) << setfill('0') << memo.fetch((i + 2)) << endl;
        }
    }

}// namespace Helper