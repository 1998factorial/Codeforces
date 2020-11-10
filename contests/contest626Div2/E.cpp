#pragma GCC optimize(3)
#pragma GCC optimize(2)
#include <bits/stdc++.h>
#define DEBUG(x) std::cerr << #x << '=' << x << std::endl
using namespace std;
typedef long long ll;
typedef pair<int , int> ii;

/*
  group the numbers in right part by their set if neighbouring
  1.intuition, if 2 nodes on right has the same set of adjcent nodes
  then we can replace these 2 nodes by 1 node with value = sum of them
*/

const int maxn = 5e5 + 10;
int N , M;
ll c[maxn];
vector<int> g[maxn];

ll gcd(ll a , ll b){
  return a == 0 ? b : gcd(b % a , a);
}

int main(){
  int t; scanf("%d" , &t);
  while(t--){
    scanf("%d %d" , &N , &M);
    for(int i = 1; i <= N; ++i)scanf("%lld" , &c[i]) , g[i].clear();
    for(int i = 1; i <= M; ++i){
      int x , y; scanf("%d %d" , &x , &y);
      g[y].push_back(x);
    }
    map<set<int> , ll> mp;
    for(int i = 1; i <= N; ++i){
      set<int> vis;
      if(g[i].empty())continue;
      for(int j : g[i]){
        vis.insert(j);
      }
      if(!g[i].empty()){
        if(mp.find(vis) == mp.end()){
          mp[vis] = 0;
        }
        mp[vis] += c[i];
      }
    }
    ll ans = 0;
    for(auto& it : mp){
      ans = gcd(ans , it.second);
    }
    printf("%lld\n" , ans);
  }

}
