#include <bits/stdc++.h>
#define int int64_t
#define MAXN 50005
using namespace std;
int t, n;
int a[MAXN];

int32_t main() {
    cin >> t;
    while (t--) {
        cin >> n;
        for (int i = 1; i <= n; i++)cin >> a[i];
        int x = a[1];
        int y = a[2];
        int z = a[n];
        if (x + y <= z) {
            cout << "1 2 " << n << endl;
        } 
        else {
            cout << -1 << endl;
        }
    }
}