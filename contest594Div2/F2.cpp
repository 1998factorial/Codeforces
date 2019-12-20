#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <vector>
#include <unordered_set>
using namespace std;
typedef long long ll;
typedef pair<int , int > ii;

const int inf = 1e9;
const int maxn = 2e6 + 10;
vector<int> g[maxn];
vector<int> s;
int dfn[maxn] , low[maxn];
bool ins[maxn];
int comp[maxn];
int N , M , cnt , ncomp;

void tarjan(int v){
  ++cnt;
  dfn[v] = low[v] = cnt;
  s.push_back(v);
  ins[v] = 1;
  for(int u : g[v]){
    if(!dfn[u]){
      tarjan(u);
      low[v] = min(low[v] , low[u]);
    }
    else if(ins[u]){
      low[v] = min(low[v] , dfn[u]);
    }
  }
  if(dfn[v] == low[v]){
    ++ncomp;
    while(!s.empty()){
      int k = s.back();
      s.pop_back();
      comp[k] = ncomp;
      ins[k] = 0;
      if(k == v)break;
    }
  }
}

int main(){
  int T;
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cin >> T;
  for(int t = 1; t <= T; ++t){
    cin >> N >> M;
    for(int i = 1; i <= 2 * N; ++i)g[i].clear();
    for(int i = 1; i <= M; ++i){
      int x , y;
      cin >> x >> y;
      if(x != y)
        g[x].push_back(y + N);
    }
    for(int i = 1; i <= N; ++i){
      g[i].push_back(i + N);
      g[i + N].push_back(i);
    }
    if(N == 1){
      cout << "No" << endl;
      continue;
    }
    cnt = 0;
    ncomp = 0;
    for(int i = 1; i <= 2 * N; ++i){
      dfn[i] = 0;
      low[i] = inf;
      ins[i] = 0;
      comp[i] = 0;
    }
    for(int i = 1; i <= 2 * N; ++i){
      if(!dfn[i])
        tarjan(i);
    }
    if(ncomp == 1){
      cout << "No" << endl;
    }
    else{
      cout << "Yes" << endl;
      int njudge = 0;
      for(int i = 1; i <= N; ++i)
        njudge += comp[i] == 1;
      cout << njudge << " " << N - njudge << endl;
      for(int i = 1; i <= N; ++i)
        if(comp[i] == 1)cout << i << " ";
      cout << endl;
      for(int i = 1; i <= N; ++i)
        if(comp[i + N] > 1)cout << i << " ";
      cout << endl;
    }
  }
}
