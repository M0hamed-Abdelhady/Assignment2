#include <iostream>
#include <vector>

using namespace std;

vector<string> split(string target, string delimiter) {
    vector<string> ret;
    string cur = "";
    for (int i = 0; i <= (int) target.size() - (int) delimiter.size(); i++)
        if (target.substr(i, delimiter.size()) == delimiter)
            ret.push_back(cur), cur = "";
        else
            cur += target[i];
    if (!cur.empty())
        ret.push_back(cur);
    return ret;
}

int main() {
    auto ret = split("10,20,30", ",");
    for (auto str: ret)
        cout << str << ' ';
    cout << endl;
    ret = split("do re mi fa so la ti do", " ");
    for (auto str: ret)
        cout << str << ' ';
    cout << endl;
    return 0;
}
