/*
    File: A2_S8_20220277_11.cpp
    Purpose: Solving Problem 11
    Author: Mohamed Ahmed Abdelhady
    Section: S8
    ID: 20220277
    TA: Khaled Ahmed
    Date: 26 Oct 2023
*/
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;


string toLowerCase(string s) {
    for (auto &i: s) {
        if (i >= 'A' && i <= 'Z')i += 32;
    }
    return s;
}

string inputFileName() {
    cout << "Input file name (must be in CWD) followed by `.txt`:";
    while (true) {
        string file;
        cin >> file;
        ifstream fin(file);
        if (fin.is_open()) {
            fin.close();
            return file;
        } else cout << "Try again:";
        fin.close();
    }
}

vector<string> getFile(string &file) {
    ifstream fin(file);
    vector<string> all;
    string line;
    while (getline(fin, line)) all.emplace_back(line);
    return all;
}

vector<string> getWords(string &sentence) {
    vector<string> all;
    string word;
    for (const char i: sentence) {
        if (i == ' ' || i == '.') {
            if (!word.empty())all.push_back(word), word = "";
        } else word.push_back(i);
    }
    if (!word.empty())all.push_back(word);
    return all;
}

void compareFiles(bool chars = false) {
    string f1 = inputFileName(), f2 = inputFileName();
    vector<string> file1 = getFile(f1), file2 = getFile(f2);
    bool identical = true;
    if (chars) {
        int different = 0;
        bool first = true;
        vector<string> print;
        string diff1, diff2;
        for (int i = 0; i < min(file1.size(), file2.size()); ++i) {
            if (file1[i].size() < file2[i].size()) {
                different += file2[i].size() - file1[i].size();
                if (first)
                    print = {to_string(i + 1), file1[i], file2[i]}, first = false;
            } else if (file1[i].size() > file2[i].size()) {
                different += file1[i].size() - file2[i].size();
                if (first)
                    print = {to_string(i + 1), file1[i], file2[i]}, first = false;
            } else {
                for (int j = 0; j < min(file1[i].size(), file2[i].size()); ++j) {
                    if (file1[i][j] != file2[i][j]) {
                        if (first)
                            print = {to_string(i + 1), file1[i], file2[i]}, first = false;
                        ++different;
                    }
                }
            }
        }
        if (file1.size() < file2.size()) {
            different += file2[file1.size()].size();
            if (first) {
                cout << different << " Different Characters\n";
                cout << "Line " << file1.size() + 1 << " different{\n" << "1 : Null ,\n2 : " << "\""
                     << file2[file1.size()] << "\"\n}";
            }
            return;
        } else if (file1.size() > file2.size()) {
            different += file1[file1.size()].size();
            if (first) {
                cout << different << " Different Characters\n";
                cout << "Line " << file1.size() + 1 << " different{\n" << "1 : " << file2[file1.size()]
                     << " ,\n2 : Null" << "\"}\n";
            }
            return;
        }
        if (print.empty())return void(cout << "identical!\n");
        cout << different << " Different Characters\n";
        cout << "Line " << print[0] << " different{\n" << "1 : \"" << print[1] << "\" ,\n2 : " << "\""
             << print[2] << "\"\n}", first = false;
    } else {
        for (int i = 0; i < min(file1.size(), file2.size()); ++i) {
            vector<string> words1 = getWords(file1[i]), words2 = getWords(file2[i]);
            for (int j = 0; j < min(words1.size(), words2.size()); ++j) {
                if (toLowerCase(words1[j]) != toLowerCase(words2[j])) {
                    cout << "Line " << i + 1 << " different{1 : \"" << words1[j] << "\" ,2 : \""
                         << words2[j] << "\"}";
                    return;
                }
            }
            if (words1.size() < words2.size()) {
                cout << "Line " << i + 1 << " different{1 : null ,2 : \""
                     << words2[words1.size()] << "\"}";
                return;
            } else if (words1.size() > words2.size()) {
                cout << "Line " << i + 1 << " different{1 : \""
                     << words1[words2.size()] << "\", 2 : Null}";
                return;
            }
        }
        if (file1.size() < file2.size()) {
            vector<string> words2 = getWords(file2[file1.size()]);
            cout << "Line " << file1.size() << " different{1 : null ,2 : \""
                 << words2.front() << "\"}";
            return;
        } else if (file1.size() > file2.size()) {
            vector<string> words1 = getWords(file2[file1.size()]);
            cout << "Line " << file1.size() << " different{1 : \""
                 << words1.front() << "\", 2 : Null}";
            return;
        }
        cout << "identical!\n";
    }
}

int main() {
    cout << "[1] Compare Character\n";
    cout << "[2] Compare Words\n";
    int x;
    cin >> x;
    compareFiles(x == 1);
    return 0;
}