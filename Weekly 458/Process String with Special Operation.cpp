class Solution {
public:
    string processStr(string s) {
        string r = "";
        for (char c : s) {
            if (c != '*' && c != '#' && c != '%') {
                r += c;
            } else if (c == '#') {
                r += r;
            } else if (c == '%') {
                reverse(r.begin(), r.end());
            } else {
                if (!r.empty()) r.pop_back();
            }
        }
        return r;
    }
};