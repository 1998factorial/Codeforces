#include <bits/stdc++.h>
#define ID if (0)
using namespace std;
int t;
string s;
int main() {
    cin >> t;
    while (t--) {
        cin >> s;
        vector<int> secs1;
        int cons1 = 0;
        for (int i = 0; i < s.length(); i++) {
            if (s[i] == '1') cons1 += 1;
            else {
                if (cons1 != 0) {
                    secs1.push_back(cons1);
                    cons1 = 0;
                }
            }
        }
        if (cons1 != 0) secs1.push_back(cons1);
        ID {
            cout << "secs1: ";
            for (int x : secs1) {
                cout << ' ' << x;
            }
            cout << endl;
        }
        sort(secs1.begin(), secs1.end());
        int answer = 0;
        for (int i = ((int) secs1.size()) - 1; i >= 0; i -= 2) {
            answer += secs1[i];
        }
        cout << answer << endl;
    }
}


