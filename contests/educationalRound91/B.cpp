#include <bits/stdc++.h>
using namespace std;

void repeat(char c, int count) {
    while (count--) cout << c;
}

int t, R, S, P;
int main() {
    cin >> t;
    while (t--) {
        string s;
        cin >> s;
        R = 0;
        S = 0;
        P = 0;
        for (char c : s) {
            if (c == 'R') R += 1;
            if (c == 'S') S += 1;
            if (c == 'P') P += 1;
        }
        if (R >= S && R >= P) repeat('P', s.length());
        else if (S >= R && S >= P) repeat('R', s.length());
        else if (P >= R && P >= S) repeat('S', s.length());
        cout << endl;
    }
}