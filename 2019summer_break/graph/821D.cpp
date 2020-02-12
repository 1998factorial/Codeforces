#include <bits/stdc++.h>
using namespace std;
typedef pair<int , int> ii;
typedef long long ll;

const int maxn = 1e4 + 10;
const ll inf = 1e18;
int N , M , K;
ii lights[maxn];
vector<ii> g[maxn * 10];
unordered_map<int , unordered_map<int , int>> mp;
ll dis[maxn * 10];
bool vis[maxn * 10];

void dijstra(int src){
  for(int i = 1; i <= K + N + M; ++i){
    dis[i] = inf;
    vis[i] = 0;
  }
  dis[src] = 0;
  priority_queue<ii , vector<ii> , greater<ii>> q;
  q.push(make_pair(dis[src] , src));
  while(!q.empty()){
    auto cur = q.top();
    q.pop();
    int v = cur.second;
    if(!vis[v]){
      vis[v] = 1;
      for(auto& e : g[v]){
        if(!vis[e.first] && dis[e.first] > dis[v] + e.second){
          dis[e.first] = dis[v] + e.second;
          q.push(make_pair(dis[e.first] , e.first));
        }
      }
    }
  }
}

void show(){
  for(int i = 1; i <= N + M + K; ++i){
    cout << i << " : ";
    for(auto& e : g[i]){
      printf("(%d , %d) , " , e.first , e.second);
    }
    cout << endl;
  }
}

int main(){
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cin >> N >> M >> K;
  for(int i = 1; i <= K; ++i){
    cin >> lights[i].first >> lights[i].second;
    int x = lights[i].first , y = lights[i].second;
    mp[x][y] = i;
  }
  if(!mp[N][M]){
    // if (N , M) is not lighted ,
    mp[N + 1][M + 1] = ++K;
    lights[K].first = N + 1;
    lights[K].second = M + 1;
  }
  // construct graph
  // search for adjcent lighted cells
  ii dir[4] = {{0 , 1} , {0 , -1} , {1 , 0} , {-1 , 0}};
  for(int i = 1; i <= K; ++i){
    for(int j = 0; j < 4; ++j){
        int dx = lights[i].first + dir[j].first;
        int dy = lights[i].second + dir[j].second;
        if(mp[dx][dy]){
          int j = mp[dx][dy];
          g[i].emplace_back(j , 0);
          g[j].emplace_back(i , 0);
        }
    }
  }
  // connect row and col cells
  for(int i = 1; i <= K; ++i){
    for(int x = -1; x < 2; ++x){
      int row = lights[i].first + x;
      if(row >= 1 && row <= N){
        int j = K + row;
        g[j].emplace_back(i , 0);
        g[i].emplace_back(j , 1);
      }
    }
    for(int y = -1; y < 2; ++y){
      int col = lights[i].second + y;
      if(col >= 1 && col <= M){
        int j = K + N + col;
        g[j].emplace_back(i , 0);
        g[i].emplace_back(j , 1);
      }
    }
  }
  dijstra(1);
  if(dis[K] >= inf){
    cout << -1 << endl;
  }
  else{
    cout << dis[K] << endl;
  }
}
