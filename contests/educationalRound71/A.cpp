#include <bits/stdc++.h>
using namespace std;

int t, b, p, f, h, c;

int main() {
    cin >> t;
    while (t--) {
        cin >> b >> p >> f;
        cin >> h >> c;
        b /= 2;
        if (h >= c) {
            int cnt1 = min(b, p);
            int cnt2 = min(b - cnt1, f);
            cout << (cnt1 * h + cnt2 * c) << endl;
        } else {
            int cnt1 = min(b, f);
            int cnt2 = min(b - cnt1, p);
            cout << (cnt1 * c + cnt2 * h) << endl;
        }
    }
}