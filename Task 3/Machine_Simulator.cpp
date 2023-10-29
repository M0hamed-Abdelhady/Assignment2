#include <fstream>
#include <iostream>
#include <windows.h>
#include "CPU.h"
#include "Helper.h"
#include "Memory.h"

vector<string> mainMenu{
        "Load Program",
        "Fetch, Decode and Execute Data",
        "Show Register",
        "Show Memory"};

int main() {
    int choice;
    ifstream fin;
    string fname;
    shared_ptr<Memory> memo = shared_ptr<Memory>(new Memory());
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CPU myCpu(memo);
       while (true) {
        try {
            choice = Helper::RunMenu(mainMenu, "Machine Language Compiler ©");
            if (choice == 1) {
                cout << "Enter File Full Name » ";
                cin >> fname;
                fin.open(fname);
                if (fin.fail() || fin.bad() || fin.bad()) throw std::runtime_error("File can not be open");
                memo->read(fin);
            } else if (choice == 2) {
                cout << "Before » ";
                Helper::showPC(myCpu);
                cout << myCpu.runCycle();
                cout << "\nAfter » ";
                Helper::showPC(myCpu);
            } else if (choice == 3) {
                SetConsoleTextAttribute(hConsole,  FOREGROUND_BLUE);
                Helper::showRegister(myCpu);
                SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_BLUE);
            } else if (choice == 4) {
                SetConsoleTextAttribute(hConsole,  FOREGROUND_GREEN);
                Helper::showMemory(*memo);
                SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_BLUE);
            }
        } catch (exception &e) {
            SetConsoleTextAttribute(hConsole,  FOREGROUND_RED);
            cerr << "╔═ ERROR: " << e.what() << ".\n╚═        Try again!\n";
            SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_BLUE);
        }
    }



    myCpu.runCycle();
}