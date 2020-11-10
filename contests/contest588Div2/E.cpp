#include <iostream>
#include <cstdio>
#include <vector>
#include <unordered_map>
using namespace std;
typedef long long ll;

const ll mod = 1e9 + 7;
const int maxn = 1e5 + 10;
int N;
vector<int> g[maxn];
ll val[maxn];
ll ret;
unordered_map<ll ,int> cnt[maxn];
/*
  find sum of f(u ,v) , u is ancestor of v
  u->a->b->v -> f(u,v) = gcd(u,a,b,v)
  for a path from root -> leaf , number of distinct gcd is at most log2(xi) = O(log2(10^12))
*/

ll gcd(ll a ,ll b){
  if(a == 0)return b;
  return gcd(b % a , a);
}

void DFS(int v , int parent){
  ret = (ret + val[v]) % mod;
  for(auto& i : cnt[v]){
    ret = (ret + i.first * i.second % mod) % mod;
  }
  ++cnt[v][val[v]];
  for(int i : g[v]){
    if(i != parent){
      for(auto& j : cnt[v]){
        cnt[i][gcd(val[i] , j.first)] += j.second;
      }
      DFS(i , v);
    }
  }
}

int main(){
  cin >> N;
  ret = 0;
  for(int i = 1; i <= N; ++i)g[i].clear();
  for(int i = 1; i <= N; ++i){
    cin >> val[i];
  }
  for(int i = 1; i <= N - 1; ++i){
    int x , y;
    cin >> x >> y;
    g[x].push_back(y);
    g[y].push_back(x);
  }
  DFS(1 , 0);
  cout << (ret + mod) % mod;
  return 0;
}
