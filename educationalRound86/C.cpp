/*
    Math, pattern
*/

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

ll gcd(ll a, ll b) {
    return a % b == 0 ? b : gcd(b, a % b);
}

int main() {
    ll t, a, b, q, l, r;
    cin >> t;
    while (t--) {
        cin >> a >> b >> q;
        ll common = gcd(a, b);
        a /= common;
        b /= common;
        ll step = a * b;
        ll width = max(a, b);
        step *= common;
        width *= common;
        while (q--) {
            cin >> l >> r;
            ll lo = l / step;
            ll hi = r / step;
            ll fulls = max(0ll , hi - (lo + 1));
            ll nots = fulls * width;
            for (ll i = lo * step; i < lo * step + width; i++) {
                if (i >= l && i <= r) nots += 1;
            }
            if (lo != hi) {
                for (ll i = hi * step; i < hi * step + width; i++) {
                    if (i >= l && i <= r) nots += 1;
                }
            }
            cout << (r-l+1) - nots << endl;
        }
    }
}
