#include <bits/stdc++.h>
using namespace std;
#define lli long double
#define INF 1180591620717411303424.0L
#define N 50
#define ID if (1)
 
lli c[55][55];
lli dp[55];
int n, m;
lli k;
bool vis[55];
int ans[55];
int main() {
    c[0][0] = 1;
    for (int i = 1; i <= N; i++) {
        for (int j = 0; j <= N; j++) {
            if (j == 0 || j == i) c[i][j] = 1;
            else {
                c[i][j] += c[i-1][j];
                c[i][j] += c[i-1][j-1];
                if (c[i][j] > INF) c[i][j] = INF;
            }
        }
    }
    // dp[n] = derangement for size n
    dp[0] = 1;
    dp[1] = 0;
    dp[2] = 1;
    for (int i = 3; i <= N; i++) {
        dp[i] = (dp[i-1]+dp[i-2])*(i-1);
        if (dp[i] > INF) dp[i] = INF;
    }
 
    cout << setprecision(100);
    cin >> n >> m >> k;
    for (int i = 1; i <= n; i++) {
        cout << "m = " << m <<endl;
        for (int j = 1; j <= n; j++) {
            if (vis[j]) continue;
            // can I put value j at position i?
            ID printf("try to assign %d at %d\n", j, i);
            if (i == j && (m-1 >= 0)) {
                lli cnt = min(c[n-i][m-1]*dp[(n-i)-(m-1)], INF);
                ID printf("would yield %Lf remaining possibilities (%Lf required)\n", cnt, k);
                if (cnt >= k) {
                    m -= 1;
                    ans[i] = j;
                    vis[j] = 1;
                    break;
                } else {
                    k -= cnt;
                }
            } else {
                lli cnt = min(c[n-i][m]*dp[(n-i)-m+1], INF);
                cout << (n-i)-m << endl;
                ID printf("would yield %Lf remaining possibilities (%Lf required)\n", cnt, k);
                if (cnt >= k) {
                    ans[i] = j;
                    vis[j] = 1;
                    break;
                } else {
                    k -= cnt;
                }
            }
        }
        if (!ans[i]) {
            cout << -1 << endl;
            return 0;
        }
        ID printf("ans[%d] = %d\n", i, ans[i]);
    }
 
    for (int i = 1; i <= n; i++) {
        cout << ans[i] << ' ';
    }
    cout << endl;
}