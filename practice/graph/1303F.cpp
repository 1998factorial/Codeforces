#pragma GCC optimize(3)
#pragma GCC optimize(2)
#include <bits/stdc++.h>
#define DEBUG(x) std::cerr << #x << '=' << x << std::endl
using namespace std;
typedef long long ll;
typedef pair<int , int> ii;

// c[i] <= c[i + 1]
/*
  input color is non decreasing
  so we can process the colors individually
  DSU does not support online remove, but this is offline, so we can do this
  by reversing the order of removal, and for each such operation we can examine
  how many connected components it can induce.
  eg, for adding, we start by marking cell (i , j) , then we check how many cells
  (i , j) is connected to. (in terms of DSU) then we know for (i , j) , we are introducing
  1 - #connection new connected components to our graph.
  similarly for remove, each time, we introduce -1 * (1 - #connection) CC to out graph
*/

const int maxq = 2e6 + 10;
const int maxn = 305;
int N , M , Q;
int color[maxn][maxn];
int inc[maxq];

vector<ii> add[maxq] , del[maxq];
int id[maxn * maxn + 10];
int sz[maxn * maxn + 10];
int dir[4][2] = {{1 , 0} , {-1 , 0} , {0 , 1} , {0 , -1}};

int find(int x){
  return x == id[x] ? x : id[x] = find(id[x]);
}

int merge(int x , int y){
  x = find(x);
  y = find(y);
  if(x == y)return 0;
  if(sz[x] > sz[y])swap(x , y);
  sz[y] += sz[x];
  id[x] = y;
  return 1;
}

void solve(vector<ii>& vec , int coef){
  for(int i = 0; i < N; ++i){
    for(int j = 0; j < M; ++j){
      color[i][j] = 0;
    }
  }
  for(int i = 0; i <= N * M; ++i)id[i] = i , sz[i] = 1;
  for(auto& e : vec){
    int x = e.first / M , y = e.first % M;
    int q = e.second;
    color[x][y] = 1;
    int val = 1; // introducing one connected component , check it's conectivity
    for(int i = 0; i < 4; ++i){
      int dx = x + dir[i][0] , dy = y + dir[i][1];
      if(dx < 0 || dx >= N || dy < 0 || dy >= M)continue;
      if(color[dx][dy]){
        if(merge(x * M + y , dx * M + dy)){ // if can merge, then we have one less connected component
          --val;
        }
      }
    }
    //cout << "resulting in change of val = " << val << endl;
    inc[q] += coef * val;
    //cout << "query " << q << " will be added by " << coef * val << endl;
  }
}


int main(){
  scanf("%d %d %d" , &N , &M , &Q);
  int c;
  for(int i = 1; i <= Q; ++i){
    int x , y; scanf("%d %d %d" , &x , &y , &c); --x; --y;
    if(color[x][y] == c)continue;
    add[c].emplace_back(x * M + y , i);
    del[color[x][y]].emplace_back(x * M + y , i);
    color[x][y] = c;
  }
  for(int i = 0; i < N; ++i){
    for(int j = 0; j < M; ++j){
      del[color[i][j]].emplace_back(i * M + j , Q + 1);
    }
  }
  for(int i = 0; i <= c; ++i){
    reverse(del[i].begin() , del[i].end());
  }
  for(int i = 0; i <= c; ++i){
    //cout << "for color = " << i << endl;
    solve(add[i] , 1);
    solve(del[i] , -1);
  }
  int cnt = 1;
  for(int q = 1; q <= Q; ++q){
    cnt += inc[q];
    printf("%d\n" , cnt);
  }
}
