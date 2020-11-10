#include <bits/stdc++.h>
#define int int64_t
#define ii pair<int,int>
#define MAXN 5005
#define INF 2305843009213693952L
#define THRESH 1305843009213693952L
#define ID if (false)
using namespace std;
int n, m;
int x[MAXN];
ii hole[MAXN];
int dp[2][MAXN];
int sd[2][MAXN]; // sd[i][j] cost to move all mice 1..j to hole i
deque<int> dq;
signed main() {
    cin >> n >> m;
    for (int i = 1; i <= n; i++) cin >> x[i];
    for (int i = 1; i <= m; i++) cin >> hole[i].first >> hole[i].second;
    // sort mice and holes in ascending position
    sort(x+1, x+1+n);
    sort(hole+1, hole+1+m);
    ID for (int i = 1; i <= n; i++) {
        printf("mouse #%ld is at %ld\n", i, x[i]);
    }
    ID for (int i = 1; i <= m; i++) {
        printf("hole #%ld is at %ld and has capacity %ld\n", i, hole[i].first, hole[i].second);
    }
    // initialize dp, note dp[*][0] remains 0
    for (int j = 1; j <= n; j++) dp[0][j] = INF;
    // use dp[i][*] to update dp[i+1][*]
    for (int i = 0; i < m; i++) {
        int curr = (i) % 2;
        int next = (i+1) % 2;
        int w = hole[i+1].second+1; // width of sliding window    
        dq.clear();
        for (int j = 1; j <= n; j++) dp[next][j] = INF;
        for (int j = 1; j <= n; j++) {
            sd[next][j] = sd[next][j-1] + abs(x[j] - hole[i+1].first);
        }
        for (int j = 0; j <= n; j++) {
            int v = dp[curr][j] - sd[next][j];
            while (dq.size() && (*dq.rbegin()) > v) dq.pop_back();
            dq.push_back(v);
            if ((j-w) >= 0) {
                int pv = dp[curr][j-w] - sd[next][j-w];
                if (dq.size() && (*dq.begin()) == pv) dq.pop_front();
            }
            dp[next][j] = *dq.begin() + sd[next][j];
            ID printf("dp[%ld][%ld] = %ld\n", next, j, dp[next][j]);
        }
    }
    if (dp[m%2][n] > THRESH) cout << -1 << endl;
    else cout << dp[m%2][n] << endl;
}