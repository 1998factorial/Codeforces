#include <bits/stdc++.h>
using namespace std;
typedef pair<int , int> ii;

const int maxn = 3e5 + 10;
set<ii> badedges;
set<int> nodes;
int N , M , K;
int deg;

bool cancon(int x , int y){
  if(x > y)swap(x , y);
  return badedges.count(make_pair(x , y)) == 0;
}

void DFS(int v){
  vector<int> adj;
  for(int i : nodes){
    if(cancon(v , i))
      adj.push_back(i);
  }
  for(int i : adj){
    nodes.erase(i);
  }
  for(int i : adj){
    DFS(i);
  }
}

bool solve(){
  if(deg < K)return 0;
  for(int i = 2; i <= N; ++i)nodes.insert(i);
  int component = 0;
  for(int i = 2; i <= N; ++i){
    if(cancon(1 , i) && nodes.count(i)){
      nodes.erase(i);
      DFS(i);
      ++component;
    }
  }
  if(component > K || nodes.size())return 0;
  return 1;
}

int main(){
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cin >> N >> M >> K;
  deg = N - 1;
  for(int i = 1; i <= M; ++i){
    int x , y; cin >> x >> y;
    if(x == 1 || y == 1)--deg;
    if(x > y)swap(x , y);
    badedges.insert(make_pair(x , y));
  }
  if(solve())cout << "possible" << endl;
  else cout << "impossible" << endl;
}
