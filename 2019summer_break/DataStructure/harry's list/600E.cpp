#pragma GCC optimize(3)
#pragma GCC optimize(2)
#include <bits/stdc++.h>
#define DEBUG(x) std::cerr << #x << '=' << x << std::endl
using namespace std;
typedef long long ll;
typedef pair<ll , ll> ii;

const int maxn = 1e5 + 10;
ll c[maxn];
int N;
vector<int> g[maxn];
int id[maxn];
map<int , ll> cnt[maxn]; // cnt[v][i] = number of color i appears in subtree rooted at v
set<ii> freq[maxn]; // (# times occur , color)
ll ans[maxn];
ll acc[maxn];

void merge(int a , int b){ // merge a to b
  int x = id[a] , y = id[b];
  if(cnt[x].size() > cnt[y].size()){
    swap(x , y);
    swap(a , b);
  }
  for(auto& e : cnt[x]){
    ll color = e.first , num = e.second;
    auto it = freq[y].rbegin();
    if(num + cnt[y][color] == it->first){
      acc[y] += color;
    }
    else if(num + cnt[y][color] > it->first){
      acc[y] = color;
    }
    freq[y].erase(make_pair(cnt[y][color] , color));
    cnt[y][color] += num;
    freq[y].insert(make_pair(cnt[y][color] , color));
  }
  id[a] = y;
}

void DFS(int v , int p){
  for(int u : g[v]){
    if(u != p){
      DFS(u , v);
    }
  }
  for(int u : g[v]){
    if(u != p){
      merge(v , u);
    }
  }
  ans[v] = acc[id[v]];
}

int main(){
  scanf("%d" , &N);
  for(int i = 1; i <= N; ++i){
    scanf("%lld" , &c[i]);
    freq[i].insert(make_pair(1 , c[i]));
    cnt[i][c[i]] = 1;
    id[i] = i;
    acc[i] = c[i];
  }
  for(int i = 1; i <= N - 1; ++i){
    int x , y; scanf("%d %d" , &x , &y);
    g[x].push_back(y);
    g[y].push_back(x);
  }
  DFS(1 , 0);
  for(int i = 1; i <= N; ++i){
    printf("%lld " , ans[i]);
  }
}
