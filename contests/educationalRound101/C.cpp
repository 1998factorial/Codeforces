#include <bits/stdc++.h>
using namespace std;
#define MAXN 200005
int t, n, k, h[MAXN];
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cin >> t;
    while (t--) {
        cin >> n >> k;
        for (int i = 1; i <= n; i++) cin >> h[i];
        bool failed = false;
        
        // maintain the range of values where the last fence can be built
        int low = h[1];
        int hgh = h[1];
        for (int i = 2; i <= n; i++) {
            hgh += (k-1);
            low -= (k-1);
            low = max(h[i], low);
            hgh = min(h[i]+(k-1), hgh);
            if (hgh < low) {
                failed = true;
                cout << "NO" << endl;
                break;
            }
        }
        if (!failed) {
            if (low <= h[n] && hgh >= h[n]) cout << "YES" << endl;
            else cout << "NO" << endl;
        }
    }
}