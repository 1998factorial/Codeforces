#include <iostream>
#include <algorithm>
using namespace std;

const int maxm = 1e6 + 10;
const int maxn = 3e5 + 10;
int N , M , tot;

int sum[maxm << 2];

void add(int pos , int val){
  while(pos <= maxm){
    sum[pos] += val;
    pos += pos & (-pos);
  }
}

int ask(int pos){
  int ret = 0;
  while(pos){
    ret += sum[pos];
    pos -= pos & (-pos);
  }
  return ret;
}

struct query{
  int l , r , id;
  query(){}
  query(int a , int b , int c ) : l(a) , r(b) , id(c) {}
  bool operator < (const query& rhs) const {
    if(l == rhs.l){
      if(r == rhs.r)return id < rhs.id;
      return r < rhs.r;
    }
    return l > rhs.l;
  }
} Q[maxn * 4];

int ans[maxn * 4];

int main(){
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cin >> N >> M;
  tot = 0;
  for(int i = 1; i <= N; ++i){
    ++tot;
    cin >> Q[tot].l >> Q[tot].r;
    Q[tot].id = 0; // segments
  }
  for(int i = 1; i <= M; ++i){
    int cnt; cin >> cnt;
    int pre = 1;
    for(int j = 1; j <= cnt; ++j){
      int x; cin >> x;
      if(j == 1){
        if(x - 1 >= 1)
          Q[++tot] = query(1 , x - 1 , i);
      }
      else{
        if(x - 1 >= pre + 1){
          Q[++tot] = query(pre + 1 , x - 1 , i);
        }
      }
      pre = x;
    }
    Q[++tot] = query(pre + 1 , maxm - 1 , i);
  }
  sort(Q + 1 , Q + 1 + tot);
  for(int i = 1; i <= tot; ++i){
    if(Q[i].id){
      ans[Q[i].id] += ask(Q[i].r);
    }
    else{
      add(Q[i].r , 1);
    }
  }
  for(int i = 1; i <= M; ++i){
    cout << N - ans[i] << endl;
  }
}
