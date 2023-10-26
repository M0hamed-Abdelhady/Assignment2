#include <bits/stdc++.h>


int main() {
    std::ifstream fin("A2_S8_20220008_10_in.txt");
    std::ofstream fout("A2_S8_20220008_10_out.txt");
    std::string s;
    std::map<std::string, std::string> cipher{
            {u8"فلسطين", u8"فـ.لـ.سـ.ـطـ.ـيـ.ـن"},
            {u8"موت", u8"مـ.ـو.،ت"},
            {u8"اسرائيل", u8"اسـ.رآيـ.ـئـ.ـل"},
            {u8"قتل", u8"قـ.ـتـ.ـل"},
            {u8"يهود", u8"يـ.ـهـ.ـو.د"},
            {u8"صهاينة", u8"صـ.ـهـ.ـا.يـ.ـنـ.ـة"},
            {u8"قتلة", u8"قـ.ـتـ.ـلـ.ـة"},
    };
    while (getline(fin, s)) {
        std::istringstream line(s);
        while (line >> s) {
            for (const auto &[a, b]: cipher) {
                size_t ind = s.find(a);
                if (ind != std::string::npos)
                    s.replace(ind, a.size(), b);
            }
            fout << s << " ";
        }
        fout << std::endl;
    }
    fin.close();
    fout.close();
}