#include <bits/stdc++.h>

using namespace std;

map<string, string> inclusive{{"he",      "he/she"},
                              {"him",     "him/her"},
                              {"himself", "himself/herself"}};

string toLowerCase(string s) {
    for (auto &i: s) {
        if (i >= 'A' && i <= 'Z')i += 32;
    }
    return s;
}

void replace(string &word, bool &Upper) {
    if (inclusive.count(toLowerCase(word)))word = inclusive[toLowerCase(word)];
    if (Upper) {
        word.front() -= 32;
        auto it = word.find('/');
        word[it + 1] -= 32;
        Upper = false;
    }
}

string replaceMasculinePronouns(string &sentence) {
    string newSentence, word;
    bool Upper;
    if (sentence[0] >= 'A' && sentence[0] <= 'Z')Upper = true;
    for (int i = 0; i < sentence.size(); ++i) {
        if (sentence[i] == ' ' || sentence[i] == '.') {
            replace(word, Upper);
            newSentence += word;
            newSentence.push_back(sentence[i]);
            word = "";
            if (sentence[i + 1] >= 'A' && sentence[i + 1] <= 'Z')Upper = true;
        } else word.push_back(sentence[i]);
    }
    replace(word, Upper);
    newSentence += word;
    return newSentence;
}

int main() {
    cout << "Input sentence to convert male speech to inclusive speech that includes both male and female\n>>";
    string sentence;
    getline(cin, sentence);
    cout << replaceMasculinePronouns(sentence) << '\n';
    return 0;
}
