#include <bits/stdc++.h>
using namespace std;

/*
  I was wrong :(
*/

const int maxn = 3e5 + 10;
int N , M , K;
multiset<int> g[maxn];
int candeg[maxn];
bool done[maxn];
int a[maxn];

int find(int x){
  return a[x] == x ? x : a[x] = find(a[x]);
}

void add(int x , int y){
  x = find(x);
  y = find(y);
  if(x != y)a[x] = y;
}

bool solve(){
  if(candeg[1] < K)return 0;
  for(int i = 2; i <= N; ++i){
    //if(g[1].find(i) != g[1].end())continue;
    for(int j = 2; j <= N; ++j){
      if(g[i].count(j) == 0){
        add(i , j);
        done[i] = done[j] = 1;
        break;
      }
    }
  }
  unordered_set<int> vis , onecan;
  for(int i = 2; i <= N; ++i){
    int par = find(i);
    vis.insert(par);
    if(g[1].count(i) == 0){ // can choose
      onecan.insert(par);
    }
  }
  if(vis.size() > onecan.size())return 0; // exists connected component that 1 can not reach
  return vis.size() <= K; // we can split some components
}

int main(){
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cin >> N >> M >> K;
  for(int i = 1; i <= N; ++i)candeg[i] = N - 1 , a[i] = i;
  for(int i = 1; i <= M; ++i){
    int x , y; cin >> x >> y;
    g[x].insert(y);
    g[y].insert(x);
    --candeg[x] , --candeg[y];
  }
  if(solve())cout << "possible" << endl;
  else cout << "impossible" << endl;
}
