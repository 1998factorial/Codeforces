#include <iostream>
#include <cstdio>
#include <cmath>
#include <cstring>
#include <algorithm>
#include <string>
#include <vector>
#include <stack>
#include <queue>
#include <set>
#include <map>
#include <sstream>
#include <complex>
#include <ctime>
#include <cassert>
#include <functional>

using namespace std;

typedef long long ll;
typedef vector<int> VI;
typedef pair<int,int> PII;

#define REP(i,s,t) for(int i=(s);i<(t);i++)
#define FILL(x,v) memset(x,v,sizeof(x))

const int INF = (int)1e9;
#define MAXN 200005

double f[MAXN];
double solve(int k, int s) {
  // cerr << k << " " << s << endl;
  double ans = 0;
  REP(i,0,s) {
    double sol = f[k] - f[k - i] - f[i] - k;
    ans += pow(2.0, sol);
  }
  return ans;
}
// int block[305][305];
// double dp[305][305];
int main() {
  // freopen("input", "r", stdin);
  int cs;
  cin >> cs;
  REP(i,1,MAXN) f[i] = f[i - 1] + log2(i);
  REP(csn, 1, cs + 1) {
    printf("Case #%d: ", csn);
    //cerr << csn << endl;
    int W, H, L, U, R, D;
    cin >> W >> H >> L >> U >> R >> D;
    int l1 = L + D - 2, l2 = R + U - 2;
    int l1c = L - 1, l2c = U - 1;
    if (H == D) l1c = 0;
    if (W == R) l2c = 0;
    double ans = solve(l1, l1c) + solve(l2, l2c);
    printf("%.12f\n", ans);

    // FILL(block, 0);
    // REP(x,L,R+1) REP(y,U,D+1) block[x][y] = 1;
    // FILL(dp, 0);
    // dp[W][H] = 1.0;
    // for (int y = H; y >= 1; y--) {
    //   for (int x = W; x >= 1; x--) {
    //     if (block[x][y]) { dp[x][y] = 0.0; continue; }
    //     if (x == W && y == H) continue;
    //     if (x + 1 > W) dp[x][y] = dp[x][y + 1];
    //     else if (y + 1 > H) dp[x][y] = dp[x + 1][y];
    //     else dp[x][y] += 0.5 * (dp[x + 1][y] + dp[x][y + 1]);
    //   }
    // }
    // double acans = dp[1][1];
    // printf("ac=%.12f err=%.12f\n", acans, fabs(acans - ans));
    // assert(fabs(acans - ans) < 1e-6);
  }
  return 0;
}
