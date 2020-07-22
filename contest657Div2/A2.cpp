#include <bits/stdc++.h>
using namespace std;
 
int t, n;
string s, s1;
string v = "abacaba";
 
bool solve(int start) {
    s1 = "";
    for (int i = 0; i < start; i++) {
        if (s[i] == '?') s1 += 'z';
        else s1 += s[i];
    }
    for (int i = start; i < start + 7; i++) {
        if (s[i] != v[i-start] && s[i] != '?') return false;
        s1 += v[i-start];
    }
    for (int i = start + 7; i < n; i++) {
        if (s[i] == '?') s1 += 'z';
        else s1 += s[i];
    }
 
    int cnt = 0;
    for (start = 0; start < n - 6; start++) {
        int ok = true;
        for (int i = 0; i < v.length(); i++) {
            if (s1[i + start] != v[i]) {
                ok = false;
                break;
            }
        }
        if (ok) ++cnt;
    }
 
    return cnt == 1;
}
 
int main() {
    cin >> t;
    while (t--) {
        cin >> n;
        cin >> s;
        int found = 0;
        for (int start = 0; start < n - 6; start++) {
            if (solve(start)) {
                found = true;
                cout << "Yes" << endl;
                cout << s1 << endl;
                break;
            }
        }
        if (!found) {
            cout << "No" << endl;
        }
    }
}



