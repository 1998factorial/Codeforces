#include <iostream>
#include <cstring>
#include <algorithm>
#include <cstdio>
#include <vector>
using namespace std;
typedef long long ll;
const int maxn = 2e5 + 10;
vector<int> pos[maxn];
vector<int> rows;
vector<int> safe;
bool vis[maxn];
int n,m,k,q;
ll dp[maxn][2];
ll inf = 1ll << 55;

int main(){
  cin >> n >> m >> k >> q;
  memset(vis,false,sizeof(vis));
  for(int i = 1; i <= k; ++i){
    int x,y;
    cin >> x >> y;
    pos[x].push_back(y);
    if(!vis[x])
      vis[x] = true,rows.push_back(x);
  }
  if(!vis[1]){
    rows.push_back(1);
    pos[1].push_back(1);
  }
  for(int i = 1; i <= q; ++i){
    int x;
    cin >> x;
    safe.push_back(x);
  }
  sort(safe.begin(),safe.end());
  sort(rows.begin(),rows.end(),[&](int a, int b){
    return a > b;
  });
  for(int i : rows){
    sort(pos[i].begin(),pos[i].end());
  }
  dp[0][0] = pos[rows[0]][pos[rows[0]].size() - 1] - pos[rows[0]][0];
  dp[0][1] = dp[0][0];
  //top to bottom
  for(int i = 1; i < rows.size(); ++i){
    int row = rows[i];
    int prow = rows[i - 1];
    int l = pos[row][0], r = pos[row][pos[row].size() - 1];
    int lp = pos[prow][0], rp = pos[prow][pos[prow].size() - 1];
    int pos1 = lower_bound(safe.begin(), safe.end(), lp) - safe.begin();
    int pos3 = lower_bound(safe.begin(), safe.end(), rp) - safe.begin();
    ll dis[8];
    for(int i = 0; i < 8; ++i)
      dis[i] = inf;
    if(pos1 != q){
      // to right from lp , can go to l or r
      dis[0] = (ll)abs(lp - safe[pos1]) + abs(r - safe[pos1]) + abs(r - l); // to l
      dis[4] = (ll)abs(lp - safe[pos1]) + abs(l - safe[pos1]) + abs(r - l); // to r
    }
    if(pos1 > 0){
      int pos2 = pos1 - 1;
      // from lp to left, to l or r
      dis[1] = (ll)abs(lp - safe[pos2]) + abs(r - safe[pos2]) + abs(r - l);
      dis[5] = (ll)abs(lp - safe[pos2]) + abs(l - safe[pos2]) + abs(r - l);
    }
    if(pos3 != q){
      //from rp to l or r
      dis[2] = (ll)abs(rp - safe[pos3]) + abs(r - safe[pos3]) + abs(r - l);
      dis[6] = (ll)abs(rp - safe[pos3]) + abs(l - safe[pos3]) + abs(r - l);
    }
    if(pos3 > 0){
      int pos2 = pos3 - 1;
      dis[3] = (ll)abs(rp - safe[pos2]) + abs(r - safe[pos2]) + abs(r - l);
      dis[7] = (ll)abs(rp - safe[pos2]) + abs(l - safe[pos2]) + abs(r - l);
    }
    dp[i][0] = abs(row - prow) + min(dp[i - 1][0] + min(dis[0] , dis[1]), dp[i - 1][1] + min(dis[2] , dis[3]));
    dp[i][1] = abs(row - prow) + min(dp[i - 1][0] + min(dis[4] , dis[5]), dp[i - 1][1] + min(dis[6] , dis[7]));
  }
  ll ans = dp[rows.size() - 1][0] + pos[1][0] - 1;
  cout << ans << endl;
}
