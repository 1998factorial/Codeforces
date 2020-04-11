#pragma GCC optimize(3)
#pragma GCC optimize(2)
#include <bits/stdc++.h>
#define DEBUG(x) std::cerr << #x << '=' << x << std::endl
using namespace std;
typedef long long ll;
typedef pair<int , int> ii;

int T , N , K;
int a[55][55];
const int maxn = 1e5 + 10;
const int inf = 1e9 + 10;
/*
  first , a diagonal has a latin square iff no number appears exactly N - 1 times
  we can greedy the diagonal
  After this, we can use bipartite matching to complete the square
  since each col/row can have at most one number x, so putting x on a[i][j] is the same as
  taking a matching of row i to col j
  Assume we have done matching for 1...k , all other cols/rows node have outdegree exactly
  N - k, therefore, hall's theorm holds, perfect matching always exists
  So we can just keep running bipartite matching and will eventually get the latin square
*/
struct bipartite_matching{
  vector<int> g[maxn];
  int N , match[maxn] , dist[maxn];
  void init(int n){
    this->N = n;
    for(int i = 0; i <= N; ++i)g[i].clear();
    memset(match , 0 , sizeof(match));
    memset(dist , 0 , sizeof(dist));
  }

  void add(int a , int b){ // add edge going from a to b
    g[a].push_back(b);
  }

  bool BFS(){
    queue<int> q;
    for(int i = 1; i <= N; ++i){
      if(match[i] == 0){
        dist[i] = 0;
        q.push(i);
      }
      else{
        dist[i] = inf;
      }
    }
    dist[0] = inf;
    while(!q.empty()){
      int u = q.front(); q.pop();
      if(u != 0){
        for(int v : g[u]){
          if(dist[match[v]] == inf){
            dist[match[v]] = dist[u] + 1;
            q.push(match[v]);
          }
        }
      }
    }
    return dist[0] != inf;
  }

  bool DFS(int u){
    if(u != 0){
      for(int v : g[u]){
        if(dist[match[v]] == dist[u] + 1){
          if(DFS(match[v])){
            match[v] = u;
            match[u] = v;
            return 1;
          }
        }
      }
      dist[u] = inf;
      return 0;
    }
    return 1;
  }

  int solve(){ // compute bipartite matching using hopcroft karp algorithm
    int ret = 0;
    while(BFS()){
      for(int i = 1; i <= N; ++i){
        if(match[i] == 0 && DFS(i)){
          ++ret;
        }
      }
    }
    return ret;
  }

};

void NO(){
  cout << "IMPOSSIBLE\n";
}

void YES(){
  cout << "POSSIBLE\n";
}

void show(){
  for(int i = 1; i <= N; ++i){
    for(int j = 1; j <= N; ++j){
      cout << a[i][j] << " ";
    }
    cout << endl;
  }
}

void go(int num){
  bipartite_matching G;
  G.init(N);
  bitset<55> cols , rows;
  cols.reset(); rows.reset();
  for(int i = 1; i <= N; ++i){
    for(int j = 1; j <= N; ++j){
      if(a[i][j] == num){ // for num , we know that we can not choose row i and col j
        rows[i] = 1;
        cols[j] = 1;
      }
    }
  }
  for(int i = 1; i <= N; ++i){
    if(rows[i])continue;
    for(int j = 1; j <= N; ++j){
      if(!cols[j] && a[i][j] == -1){
        // we can match row i to col j iff row i and col j has no num on them and ceil a[i][j] has not taken
        G.add(i , j + N);
      }
    }
  }
  int ret = G.solve();
  for(int i = 1; i <= N; ++i){
    if(G.match[i] != 0){
      a[i][G.match[i] - N] = num;
    }
  }
}

void solve(){
  if(K < N || K > N * N || K == N + 1 || K == N * N - 1 || (N == 3 && K == 5) || (N == 3 && K == 7)){
    NO();
    return;
  }
  YES();
  // greedy a diagonal
  memset(a , -1 , sizeof(a));
  for(int i = 1; i <= N; ++i){
    a[i][i] = K / N;
  }
  int r = K % N;
  if(r == 1){
    ++a[1][1]; ++a[2][2]; --a[3][3];
  }
  else if(r == N - 1){
    for(int i = 1; i <= N; ++i)++a[i][i];
    --a[1][1]; --a[2][2]; ++a[3][3];
  }
  else {
    for(int i = 1; i <= r; ++i)++a[i][i];
  }
  unordered_map<int , int> cnt;
  // fill the numbers that have least choices first
  vector<int> nums;
  for(int i = 1; i <= N; ++i){
    ++cnt[a[i][i]]; nums.push_back(i);
  }
  sort(nums.begin() , nums.end() , [&](int x , int y){
    return cnt[x] > cnt[y];
  });
  for(int i : nums){
    go(i);
  }
  show();
}

int main(){
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cin >> T;
  for(int t = 1; t <= T; ++t){
    cin >> N >> K;
    cout << "Case #" << t << ": ";
    solve();
  }
}
