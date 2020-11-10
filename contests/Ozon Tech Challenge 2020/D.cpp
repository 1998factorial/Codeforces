#pragma GCC optimize(3)
#pragma GCC optimize(2)
#include <bits/stdc++.h>
#define DEBUG(x) std::cerr << #x << '=' << x << std::endl
using namespace std;
typedef long long ll;
typedef pair<int , int> ii;

/*
  interactive
  for any 2 leafs x y
  lca(x , y) = w
  if w = x | w = y, then root is w
  if neither, then we erase x and y from tree and append new leafs
  at the end, if there is only one leaf, then the root is this leaf
*/

const int maxn = 1005;
unordered_set<int> g[maxn];
int N;

int ask(int x , int y){
  cout << "? " << x << " " << y << endl;
  cout.flush();
  int r; cin >> r;
  return r;
}

void answer(int x){
  cout << "! " << x << endl;
  cout.flush();exit(0);
}

int main(){
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cin >> N;
  for(int i = 1; i < N; ++i){
    int x , y; cin >> x >> y;
    g[x].insert(y);
    g[y].insert(x);
  }
  vector<int> leaf;
  for(int i = 1; i <= N; ++i){
    if(g[i].size() == 1)
      leaf.push_back(i);
  }
  while(leaf.size() > 1){
    int x = leaf.back(); leaf.pop_back();
    int y = leaf.back(); leaf.pop_back();
    int w = ask(x , y);
    if(w == x || w == y)answer(w);
    for(int u : g[x]){
      g[u].erase(x);
      if(g[u].size() == 1)leaf.push_back(u);
    }
    g[x].clear();
    for(int u : g[y]){
      g[u].erase(y);
      if(g[u].size() == 1)leaf.push_back(u);
    }
    g[y].clear();
  }
  answer(leaf.back());
}
