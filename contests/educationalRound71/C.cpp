#include <bits/stdc++.h>
#define MAXN 200005
using namespace std;
typedef long long ll;
const ll INF = 1e18;
ll t, n, a, b;
string s;
ll DP[MAXN][2];


int main() {
    cin >> t;
    while (t--) {
        cin >> n >> a >> b;
        cin >> s;
        for (int i = 0; i <= n; i++) {
            DP[i][0] = INF;
            DP[i][1] = INF;
        }
        DP[0][0] = b;
        for (int i = 1; i <= n; i++) {
            DP[i][1] = min(DP[i][1], DP[i - 1][1]+(1ll * a)+(2ll * b));
            DP[i][1] = min(DP[i][1], DP[i - 1][0]+(2ll * a)+(2ll * b));
            if (s[i - 1] == '0' && (i == s.length() || s[i] == '0')) {
                DP[i][0] = min(DP[i][0], DP[i - 1][1]+(2ll * a)+(1ll * b));
                DP[i][0] = min(DP[i][0], DP[i - 1][0]+(1ll * a)+(1ll * b));
            }
        }
        cout << DP[n][0] << endl;
    }
}


