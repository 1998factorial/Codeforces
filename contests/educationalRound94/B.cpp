#include <bits/stdc++.h>
#define ll int64_t
using namespace std;
 
void swap_vars(ll &a, ll &b) {
    ll tmp = a;
    a = b;
    b = tmp;
}
 
ll t, p, f, cs, cw, s, w;
int main() {
    // a * s + b * w <= p
    // c * s + d * w <= f
    // a + c <= cs
    // b + d <= cw
    cin >> t;
    while (t--) {
        cin >> p >> f >> cs >> cw >> s >> w;
        if (s > w) {
            swap_vars(cs, cw);
            swap_vars(s, w);
        }
        ll best = 0;
        for (int use_cs = 0; use_cs <= cs; use_cs++) {
            // take use_cs swords for myself
            ll score = use_cs;
            if (use_cs * s > p) continue;
            ll remain_p = p - use_cs * s;
            ll use_cw = remain_p / w;
            use_cw = min(use_cw, cw); // how many waraxes to take for myself
            score += use_cw;
            ll remain_cs = cs - use_cs;
            ll remain_cw = cw - use_cw;
 
            ll use_cs_f = min(f / s, remain_cs);
            ll use_cw_f = min((f - use_cs_f * s) / w, remain_cw);
            score += use_cs_f;
            score += use_cw_f;
            best = max(best, score);
        }
        cout << best << endl;
    }
}