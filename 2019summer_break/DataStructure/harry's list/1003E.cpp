#pragma GCC optimize(3)
#pragma GCC optimize(2)
#include <bits/stdc++.h>
#define DEBUG(x) std::cerr << #x << '=' << x << std::endl
using namespace std;
typedef long long ll;
typedef pair<int , int> ii;
/*
  constructive
  build path first of length D first
  maintain a stack to contain the candidates for v in [D + 2 .. N]
  check degree and distances
*/
const int maxn = 4e5 + 10;
int N , D , K;
vector<int> g[maxn];
vector<ii> edges;
int deg[maxn];
int dis[maxn];

void solve(){
  bool ok = 1;
  vector<int> can;
  for(int i = 1; i <= D && ok; ++i){
    edges.emplace_back(i , i + 1);
    ++deg[i];
    ++deg[i + 1];
    dis[i] = max(i - 1 , D - i + 1);
    dis[i + 1] = max(i , D - i);
    if(deg[i] > K)ok = 0;
  }
  for(int i = 1; i <= D + 1 && ok; ++i){
    if(dis[i] < D && deg[i] < K){
      can.push_back(i);
    }
  }
  for(int i = D + 2; i <= N && ok; ++i){
    if(can.empty()){
      ok = 0;
    }
    else{
      bool f = 0;
      while(!can.empty() && !f){
        int x = can.back();
        if(deg[x] >= K)can.pop_back();
        else{
          ++deg[x];
          ++deg[i];
          edges.emplace_back(i , x);
          dis[i] = dis[x] + 1;
          if(dis[i] < D && deg[i] < K)can.push_back(i);
          f = 1;
        }
      }
      if(!f)ok = 0;
    }
  }
  if(!ok){
    printf("NO\n");
  }
  else{
    printf("YES\n");
    for(auto& e : edges){
      printf("%d %d\n" , e.first , e.second);
    }
  }
}

int main(){
  scanf("%d %d %d" , &N , &D , &K);
  if(D + 1 > N){
    printf("NO\n");
  }
  else{
    solve();
  }
}
