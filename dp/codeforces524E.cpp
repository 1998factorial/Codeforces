#include <iostream>
#include <algorithm>
#include <cstring>
#include <cstdio>
using namespace std;
typedef pair<int , int> ii;

const int inf = 1 << 28;
const int maxn = 2e5 + 10;
int N , M , K , Q;
ii pos[maxn];
int tree[maxn << 2];
bool ans[maxn];
struct query{
  ii a , b;
  int id;
  bool operator<(const query& other) const{
    return b < other.b;
  }
}q[maxn];

/*
given a NxM chessboard and positions of K rooks.
given Q rectangles , we need to determine if in each of the rectangles that each
ceil can be attacked by some rook that are also in this rectangle.
*/

void update(int pos , int val , int l , int r , int id){
  if(l > r || pos > r || pos < l)return;
  if(l == r){
    tree[id] = max(tree[id] , val);
  }
  else{
    int m = (l + r) >> 1;
    update(pos , val , l , m , id << 1);
    update(pos , val , m + 1 , r , id << 1 | 1);
    tree[id] = min(tree[id << 1] , tree[id << 1 | 1]);
  }
}

int query(int l , int r , int x , int y , int id){
  if(l <= x && y <= r){
    return tree[id];
  }
  int m = (x + y) >> 1;
  if(m < l){
    return query(l , r , m + 1 , y , id << 1 | 1);
  }
  if(m >= r){
    return query(l , r , x , m , id << 1);
  }
  return min(query(l , r , x , m , id << 1) , query(l , r , m + 1 , y , id << 1 | 1));
}

void solve(){
  sort(pos + 1 , pos + 1 + K);
  sort(q + 1 , q + Q + 1);
  int j = 1;
  int up = max(N , M);
  memset(tree , 0 , sizeof(tree));
  for(int i = 1; i <= Q; ++i){
    while(j <= K && pos[j] <= q[i].b)update(pos[j].second , pos[j].first , 1 , up , 1) , ++j;
    int miny = query(q[i].a.second , q[i].b.second , 1 , up , 1);
    if(miny >= q[i].a.first)ans[q[i].id] = true;
  }
}


int main(){
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cin >> N >> M >> K >> Q;
  for(int i = 1; i <= K; ++i){
    cin >> pos[i].first >> pos[i].second;
  }
  for(int i = 1; i <= Q; ++i){
    cin >> q[i].a.first >> q[i].a.second;
    cin >> q[i].b.first >> q[i].b.second;
    q[i].id = i;
    ans[i] = false;
  }
  solve(); //check for columns first
  // swap x and y
  for(int i = 1; i <= K; ++i){
    swap(pos[i].first , pos[i].second);
  }
  for(int i = 1; i <= Q; ++i){
    swap(q[i].a.first , q[i].a.second);
    swap(q[i].b.first , q[i].b.second);
  }
  solve(); //check for colums (rows)
  for(int i = 1; i <= Q; ++i){
    if(ans[i])cout << "YES\n";
    else cout << "NO\n";
  }
}
