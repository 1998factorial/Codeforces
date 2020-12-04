#include <bits/stdc++.h>
using namespace std;

const int INF = 1e9;

int t, keys, a[10005], dp[10005][4];

int main() {
    cin >> t;
    for (int iter = 1; iter <= t; iter++) {
        cin >> keys;
        for (int i = 0; i < keys; i++) cin >> a[i];
        for (int i = 0; i < keys; i++)
            for (int j = 0; j < 4; j++)
                dp[i][j] = INF;
        for (int i = 0; i < 4; i++) dp[0][i] = 0;
        for (int i = 1; i < keys; i++) {
            int oldnote = a[i - 1];
            int newnote = a[i];
            for (int j = 0; j < 4; j++) {
                for (int k = 0; k < 4; k++) {
                    if (oldnote > newnote) {
                        if (j > k) {
                            dp[i][k] = min(dp[i][k], dp[i - 1][j]);
                        } else {
                            dp[i][k] = min(dp[i][k], dp[i - 1][j] + 1);
                        }
                    } else if (oldnote == newnote) {
                        if (j == k) {
                            dp[i][k] = min(dp[i][k], dp[i - 1][j]);
                        } else {
                            dp[i][k] = min(dp[i][k], dp[i - 1][j] + 1);
                        }
                    } else if (oldnote < newnote) {
                        if (j < k) {
                            dp[i][k] = min(dp[i][k], dp[i - 1][j]);
                        } else {
                            dp[i][k] = min(dp[i][k], dp[i - 1][j] + 1);
                        }
                    }
                }
            }
        }
        int ans = INF;
        for (int i = 0; i < 4; i++) {
            ans = min(ans, dp[keys - 1][i]);
        }
        printf("Case #%d: %d\n", iter, ans);
    }
}
