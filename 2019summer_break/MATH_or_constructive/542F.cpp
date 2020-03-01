#include <bits/stdc++.h>
using namespace std;

/*
  start from the most bottom layer
  pick 2 largest values and put them to current level + 1
  these 2 values can represent either: 2 tasks that cost i time
  or 1 task that cost i time and accumulated values from previous levels
*/


int N , T;
const int maxn = 1e3 + 10;
vector<int> g[105];

int main(){
  cin >> N >> T;
  for(int i = 1; i <= N; ++i){
    int t , q; cin >> t >> q;
    g[t].push_back(q);
  }
  for(int i = 1; i <= T; ++i){
    sort(g[i].begin() , g[i].end() , [&](int x , int y){
      return x > y;
    });
    for(int j = 0; j < g[i].size(); j += 2){
      if(j + 1 < g[i].size())
        g[i + 1].push_back(g[i][j] + g[i][j + 1]);
      else
        g[i + 1].push_back(g[i][j]);
    }
  }
  cout << g[T][0] << endl;
}
