#include <bits/stdc++.h>
#define int int64_t
#define ID if (0)
using namespace std;
int n, q, x;
int jumps(int x) {
    if (x % 2 == 1) return 0;
    return n - (x/2);
}
int32_t main() {
    cin >> n >> q;
    ID for (int i = 1; i <= (n*2); i++) {
        cout << "jumps[" << i << "] = " << jumps(i) << endl;
    }
    while (q--) {
        cin >> x;
        int j = jumps(x);
        int at = x;
        while (true) {
            if (at % 2 == 1) break;
            at += j;
            j = j / 2;
        }
        cout << (at + 1) / 2 << endl;
    }
}


