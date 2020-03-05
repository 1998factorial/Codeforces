#pragma GCC optimize(3)
#pragma GCC optimize(2)
#include <bits/stdc++.h>
#define DEBUG(x) std::cerr << #x << '=' << x << std::endl
using namespace std;
typedef long long ll;
typedef pair<int , int> ii;

int N , M , K;
const int maxn = 1e5 + 10;
bool ban[maxn];
bool del[maxn];
int deg[maxn];
int deg2[maxn];
unordered_set<int> g[maxn];

/*
  O(NlogN) method
  
*/

bool check(double mid){
  memset(del , 0 , sizeof(del));
  memset(deg2 , 0 , sizeof(deg2));
  for(int i = 1; i <= N; ++i){
    if(!ban[i]){
      for(int j : g[i]){
        if(!ban[j]){
          ++deg2[i];
        }
      }
    }
  }
  queue<int> q;
  for(int i = 1; i <= N; ++i){
    if(!ban[i] && (double)deg2[i] / deg[i] < mid){
      q.push(i);
    }
  }
  while(!q.empty()){
    int v = q.front();
    q.pop();
    if(!del[v]){
      del[v] = 1;
      for(int u : g[v]){
        if(!ban[u] && !del[u]){
          --deg2[u];
          if((double)deg2[u] / deg[u] < mid){
            q.push(u);
          }
        }
      }
      deg2[v] = 0;
    }
  }
  int ret = 0;
  for(int i = 1; i <= N; ++i){
    ret += (!ban[i] && !del[i]);
  }
  return ret > 0;
}

int main(){
  scanf("%d %d %d" , &N , &M , &K);
  for(int i = 1; i <= K; ++i){
    int x; scanf("%d" , &x);
    ban[x] = 1;
  }
  for(int i = 1; i <= M; ++i){
    int x , y; scanf("%d %d" , &x , &y);
    g[x].insert(y);
    g[y].insert(x);
    ++deg[x]; ++deg[y];
  }
  double l = 0 , r = 1.0 , best = 0;
  for(int i = 1; i <= 40; ++i){
    double mid = (l + r) / 2.0;
    if(check(mid)){
      best = mid;
      l = mid;
    }
    else{
      r = mid;
    }
  }
  // construct the set
  check(best);
  int cnt = 0;
  vector<int> ans;
  for(int i = 1; i <= N; ++i){
    if(!ban[i] && !del[i]){
      ++cnt;
      ans.push_back(i);
    }
  }
  printf("%d\n" , cnt);
  for(int i : ans)printf("%d " , i);
  printf("\n");
}
