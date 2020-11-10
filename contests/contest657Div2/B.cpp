#include <bits/stdc++.h>
#define int long long 
using namespace std;
int t, l, r, m;

signed main() {
    cin >> t;
    while (t--) {
        scanf("%lld %lld %lld" , &l , &r , &m);
        int d = r - l;
        // must be in range of m +/- d
        int lo = m - d;
        int hi = m + d;
        for (int a = l; a <= r; a++) {
            int n = hi / a;
            if (n * a >= lo) {
                int diff = m - n * a;
                int b = l;
                int c = l;
                if (diff > 0) {
                    b = l + diff;
                    c = l;
                }
                if (diff < 0) {
                    b = l;
                    c = l - diff;
                }
                printf("%lld %lld %lld\n" , a , b , c);
                break;
            }
        }
    }
}