#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

/*
  坐标系转换： 曼哈顿距离 转换至 切比雪夫距离
  问题转换至经典正方形最大点覆盖扫描线问题

  (x , y) -> (x + y , x - y)
  |x1 - x2| + |y1 - y2| = max(|x1 + y1 - x2 - y2| , |x1 - y1 - x2 + y2|)
  proof is inspried by |x - y| = max(x - y , y - x)
*/

const int maxn = 3e5 + 10;
int N , R;
vector<int> disc;
int tmp[maxn] , X[maxn] , Y[maxn];

struct event {
  int x , yl , yr , val;
  event(){}
  event(int a , int b , int c , int d) : x(a) , yl(b) , yr(c) , val(d) {}
  bool operator < (const event& rhs) const {
    return x < rhs.x;
  }
} events[maxn << 2];

struct node {
  int val , lazy;
} tree[maxn << 2];

int getindex(int x){
  return lower_bound(disc.begin() , disc.end() , x) - disc.begin();
}

void push_down(int l , int r , int id){
  if(l < r){
    tree[id << 1].val += tree[id].lazy;
    tree[id << 1 | 1].val += tree[id].lazy;
    tree[id << 1].lazy += tree[id].lazy;
    tree[id << 1 | 1].lazy += tree[id].lazy;
    tree[id].lazy = 0;
  }
}

void update(int l , int r , int x , int y , int id , int val){
  if(l > r || x > y || x > r || y < l)return;
  if(l <= x && y <= r){
    tree[id].val += val;
    tree[id].lazy += val;
  }
  else{
    int mid = (x + y) >> 1;
    push_down(x , y , id);
    update(l , r , x , mid , id << 1 , val);
    update(l , r , mid + 1 , y , id << 1 | 1 , val);
    tree[id].val = max(tree[id << 1].val , tree[id << 1 | 1].val);
  }
}

int main(){
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cin >> N >> R;
  vector<int> a;
  for(int i = 0; i < N; ++i){
    int x , y; cin >> x >> y;
    X[i] = x + y;
    Y[i] = x - y;
    a.push_back(Y[i]);
    a.push_back(Y[i] - R);
    a.push_back(Y[i] + R);
  }
  sort(a.begin() , a.end());
  int cnt = unique(a.begin() , a.end()) - a.begin();
  for(int i = 0; i < cnt; ++i){
    disc.push_back(a[i]);
  }
  int nevents = 0;
  for(int i = 0; i < N; ++i){
    events[++nevents] = event(X[i] - R , getindex(Y[i] - R) , getindex(Y[i] + R) , 1);
    events[++nevents] = event(X[i] + R + 1 , getindex(Y[i] - R) , getindex(Y[i] + R) , -1);
  }
  sort(events + 1 , events + nevents);
  int ans = 0;
  for(int i = 1; i <= nevents; ){
    int j = i;
    while(j <= nevents && events[i].x == events[j].x){
      update(events[j].yl , events[j].yr , 0 , cnt , 1 , events[j].val); // update range tree
      ++j;
    }
    // update ans
    ans = max(ans , tree[1].val);
    i = j;
  }
  cout << ans << endl;
}
