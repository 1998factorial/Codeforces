#include <bits/stdc++.h>
using namespace std;
int t, x;
string w, s;
int main() {
    cin >> t;
    while (t--) {
        cin >> s >> x;
        w = s;
        for (int i = 0; i < w.length(); i++) w[i] = '1';
        for (int i = 0; i < s.length(); i++) {
            if (s[i] == '0') {
                if (i-x >= 0) w[i-x] = '0';
                if (i+x < w.length()) w[i+x] = '0';
            }
        }
        bool solvable = true;
        for (int i = 0; i < s.length(); i++) {
            char intended = '0';
            if (i-x >= 0 && w[i-x] == '1') intended = '1';
            if (i+x < w.length() && w[i+x] == '1') intended = '1';
            if (intended != s[i]) {
                cout << -1 << endl;
                solvable = false;
                break;
            }
        }
        if (solvable) {
            cout << w << endl;
        }
    }
}


