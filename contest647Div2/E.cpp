#include <bits/stdc++.h>
#define ID if (0)
#define x first
#define y second
using namespace std;
typedef long long int ll;
const ll mod = 1000000007L;
const ll N = 1000100;
ll t, n, p, k[N];
ll qpow(ll x, ll n) {
    ll ret = 1;
    while (n) {
        if (n & 1) ret = (ret * x) % mod;
        x = (x * x) % mod;
        n >>= 1;
    }
    return ret;
}
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cin >> t;
    while (t--) {
        map<int, int> pcnt;
        cin >> n >> p;
        for (int i = 1; i <= n; i++) {
            cin >> k[i];
            pcnt[k[i]] += 1;
        }
        if (p == 1) {
            cout << (n % 2) << endl;
            continue;
        }
        // calculate floor(log(n, base = p))
        ll mpow = 1;
        ll at = n;
        while (at > p) {
            at /= p;
            mpow += 1;
        }
        ID cout << "size = " << pcnt.size() << endl;
        bool printed = false;
        ll prev = N;
        ll debt = 0;
        for (auto it = pcnt.rbegin(); it != pcnt.rend(); ++it) {
            // at this point consider debt * qpow(p, x)
            ll x = (*it).x;
            ll y = (*it).y;
            ll moves = prev - x;
            prev = x;
            ID {
                printf("\tx = %lld\n", x);
                printf("\ty = %lld\n", y);
                printf("\tmoves = %lld\n", moves);
                printf("\tmpow = %lld\n", mpow);
            }
            if ((debt && moves >= mpow) || (debt * qpow(p, moves) > n)) {
                // debt is definitely greater than the sum of remaining
                // put debt on one side, and everything else on the other
                debt *= qpow(p, moves);
                ll answer = (debt * qpow(p, x)) % mod;
                ID printf("\ttoo much debt = %lld\n", answer);
                for (auto j = it; j != pcnt.rend(); ++j) {
                    // ID printf("\tuse %lld %lld\n", ((*j).y), (*j).x);
                    answer -= ((*j).y * qpow(p, (*j).x)) % mod;
                    if (answer < 0) answer += mod;
                }
                printed = true;
                cout << answer << endl;
                break;
            }
            debt *= qpow(p, moves);
            if (y >= debt) {
                debt = (y - debt) % 2;
            } else {
                debt -= y;
            }
        }
        debt *= qpow(p, prev);
        debt %= mod;
        if (!printed) {
            cout << debt << endl;
        }
    }
}
