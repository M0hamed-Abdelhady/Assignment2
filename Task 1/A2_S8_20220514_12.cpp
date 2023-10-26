#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <sstream>

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
    map<string, int> value;
    value["urgent"] = 3;
    value["Verify"] = 3;
    value["Confirm"] = 3;
    value["Update"] = 3;
    value["Account"] = 3;
    value["Password"] = 3;
    value["Credit card"] = 3;
    value["cial security number"] = 3;
    value["Bank"] = 3;
    value["PayPal"] = 3;
    value["eBay"] = 3;
    value["Amazon"] = 3;
    value["Netflix"] = 3;
    value["Microsoft"] = 3;
    value["Google"] = 3;
    value["Apple"] = 3;
    value["Dear customer"] = 2;
    value["Your account has been suspended"] = 2;
    value["Please click on the following link to verify your account"] = 2;
    value["We have noticed some unusual activity on your account"] = 2;
    value["To protect your account, please update your password"] = 2;
    value["We need to confirm your personal information"] = 2;
    value["Your credit card information is out of date"] = 2;
    value["Please click here to update your credit card information"] = 2;
    value["Your social security number has been compromised"] = 2;
    value["Please click here to protect your social security number"] = 2;
    value["You have won a prize"] = 2;
    value["Click here to claim your prize"] = 2;
    value["Limited time offer"] = 2;
    value["Don't miss out"] = 2;
    value["Act now"] = 2;
    value["Click here to learn more"] = 2;
    value["Unsubscribe"] = 1;
    value["Privacy policy"] = 1;
    value["Contact us"] = 1;

    freopen("email.txt", "r", stdin);
    string line;
    while (cin >> line) {
        auto words = split(line, " ");
        int totalValue = 0;
        for (auto word: words)
            if (value.count(word))
                totalValue += value[word];
        if (totalValue >= 15)
            cout << "Phishing Email.";
        else
            cout << "Valid Email";
    }
    return 0;
}
// the program detected some emails from my spam emails to be phishing emails and didn't detect others
// same happened with valid emails, so it is not accurate.