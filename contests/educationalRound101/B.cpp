#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
 
int dp[102][102];
int n, m;
int a[102], b[102];
void init() {
    int i, j;
    for (i = 0 ; i < 102; ++i) {
        for (j = 0 ; j < 102; ++j) {
            dp[i][j] = -100000000;
        }
    }
}
 
int main() {
    int T, i, j;
    scanf("%d", &T);
    while (T-- > 0) {
        init();
        scanf("%d", &n);
        dp[0][0] = 0;
        for (i = 1; i <= n; ++i) {
            scanf("%d", &a[i]);
            dp[i][0] = dp[i-1][0] + a[i];
        }
 
        scanf("%d", &m);
        for (i = 1; i <= m; ++i) {
            scanf("%d", &b[i]);
            dp[0][i] = dp[0][i-1] + b[i];
        }
 
        for (i = 1; i <= n; ++i) {
            for (j = 1; j <= m; ++j) {
                dp[i][j] = max(dp[i][j], max(dp[i-1][j] + a[i], dp[i][j-1] + b[j]));
            }
        }
 
        int ans = 0;
        for (i = 0 ; i <= n; ++i) {
            for (j = 0; j <= m; ++j) {
                ans = max(ans, dp[i][j]);
            }
        }
 
        printf("%d\n", ans);
    }
    return 0;
}