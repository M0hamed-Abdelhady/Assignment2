/*
    File: A2_S8_20220277_5.cpp
    Purpose: Solving Problem 5
    Author: Mohamed Ahmed Abdelhady
    Section: S8
    ID: 20220008
    TA: Khaled Ahmed
    Date: 26 Oct 2023
*/
#include <iostream>
#include <string>
#include <vector>
#include <set>
#include <map>

using namespace std;


class Player;

map<string, Player> all;
multiset<pair<int, string>, greater<>> top10;

class Player {
    string Name;
    vector<int> Score;
    int highScore;
public:

public:
    Player() : Name(), Score{0}, highScore(0) {}

    Player(string &name, int &score) : Name(name), Score{score}, highScore(score) {}

    const string &getName() const {
        return Name;
    }

    const vector<int> &getScore() const {
        return Score;
    }

    void setName(const string &name) {
        Name = name;
    }

    int getHighScore() const {
        return highScore;
    }

    void newScore(int score) {
        Player::Score.emplace_back(score);
        highScore = max(highScore, score);
    }
};

void showTop10() {
    if (top10.empty())return void(cout << "Empty!\n");
    int j = 0;
    for (auto i = top10.begin(); i != top10.end() && j < 10; ++i, ++j)
        cout << j + 1 << ". Name: " << i->second << "Score: " << i->first << '\n';
}

string inputName(bool exist = false) {
    string name;
    cout << "Input Player Name:";
    while (true) {
        cin >> name;
        if (all.count(name) == exist)return name;
        cout << (exist ? "No such a Player Name!" : "Used Name!");
    }
}

int inputScore() {
    int score;
    cout << "Input Player Score:";
    while (true) {
        cin >> score;
        if (cin.fail()) {
            cout << "Input a valid Score:";
            continue;
        }
        return score;
    }
}

bool check(string &name) {
    int j = 0;
    for (auto i = top10.begin(); i != top10.end() && j < 10; ++i, ++j)
        if (i->second == name)return true;
    return false;
}

int getRank(string &name) {
    int j = 0;
    for (auto i = top10.begin(); i != top10.end() && j < 10; ++i, ++j)
        if (i->second == name)return j + 1;
}

void getPlayerHighScore(string &name) {
    if (!check(name))
        cout << "Player isn't in the Top 10 List, his highest score is " << all[name].getHighScore() << '\n';
    else
        cout << "Player's Rank is " << getRank(name) << "in Top 10 List and his highest score is "
             << all[name].getHighScore() << '\n';
}

void addNewScore(string &name, int &score) {
    Player x(name, score);
    all[name] = x;
    top10.insert({score, name});
}

void addNewPlayer(string &name, int &score) {
    all[name].newScore(score);
    top10.insert({score, name});
}

void removePlayer(string &Name) {
    vector<int> playerScores = all[Name].getScore();
    for (const auto &score: playerScores) {
        top10.erase(top10.find({score, Name}));
    }
    all.erase(Name);
}

int runMenu(vector<string> &menu, bool quit = true) {
    for (int i = 1; i <= menu.size(); ++i) {
        std::cout << '[' << i << "] " << menu[i - 1] << '\n';
    }
    int lowerLimit = 1;
    if (quit)std::cout << "[0] Exit\n", lowerLimit = 0;
    std::cout << "Your Choice:";
    int choice;
    while (true) {
        std::cin >> choice;
        if (std::cin.fail() || choice > menu.size() || choice < lowerLimit) {
            std::cout << "ERROR please input a number in range " << lowerLimit << " to " << menu.size() << ":";
            std::cin.ignore();
        } else return choice;

    }

}

int main() {
    vector<string> menu{"Top 10 List", "Get Player's High Score", "Add new Score", "Add new Player", "Remove a Player"};
    while (true) {
        int choice = runMenu(menu);
        if (choice == 1) showTop10();
        else if (choice == 2) {
            cout << "Input Player Name:";
            string name = inputName(true);
            getPlayerHighScore(name);
        } else if (choice == 3) {
            string name = inputName(true);
            int score = inputScore();
            addNewScore(name, score);
        } else if (choice == 4) {
            string name = inputName();
            int score = inputScore();
            addNewPlayer(name, score);
        } else if (choice == 5) {
            string name = inputName(true);
            removePlayer(name);
        } else return 0;
    }
}