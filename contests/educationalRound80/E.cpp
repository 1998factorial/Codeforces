#include <iostream>
#include <algorithm>
using namespace std;

const int maxn = 3e5 + 10;

int sum[maxn << 3];
int N , M;
int maxans[maxn] , minans[maxn] , pos[maxn];

void update(int pos , int val){
  while(pos <= N + M){
    sum[pos] += val;
    pos += pos & (-pos);
  }
}

int query(int pos){
  int ret = 0;
  while(pos){
    ret += sum[pos];
    pos -= pos & (-pos);
  }
  return ret;
}

int main(){
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cin >> N >> M;
  for(int i = 1; i <= N; ++i){
    update(i + M , 1);
    minans[i] = maxans[i] = query(i + M);
    pos[i] = i + M;
  }
  for(int i = M; i >= 1; --i){
    int x; cin >> x;
    minans[x] = 1;
    maxans[x] = max(maxans[x] , query(pos[x]));
    update(pos[x] , -1);
    pos[x] = i;
    update(pos[x] , 1);
  }
  for(int i = 1; i <= N; ++i){
    cout << minans[i] << " " << max(maxans[i] , query(pos[i])) << endl;
  }
}
