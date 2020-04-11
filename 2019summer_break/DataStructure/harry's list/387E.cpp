#pragma GCC optimize(3)
#pragma GCC optimize(2)
#include <bits/stdc++.h>
#define DEBUG(x) std::cerr << #x << '=' << x << std::endl
using namespace std;
typedef long long ll;
typedef pair<int , int> ii;

/*
  it is always good to remove from smallest to largest (exchange argument)
  for each position we are removing, we need to quickly find minimal l and maximal r
  such that a[l..pos] >= a[pos], a[pos] <= a[pos..r].
  Since N is large, if we binary search position and do range query, we will end up
  O(logN * logN) per query which is too slow. The key observation here is that since we are
  removing from smallest to largest, we can choose not to add any of the number that we are
  about to remove into the data structure that support our min query, as which ever is samller than
  my current number has already been removed (if remove). Therefore, we do not need to update our
  min query data structure, and RMQ since like a good choice to us! (O(1) query , but do not support update)
  when we have [l , r] , we can use a data structure that supports range sum query and point update.
  Fenwick tree is a good one.
  Therefore, overall time complexity : (Q * logN)
*/

const int maxn = 1e6 + 10;
const int inf = 1e9 + 10;

int N , K;
int p[maxn];
int mp[maxn];
bool stay[maxn];
int logs[maxn];
vector<int> re;
int sum[maxn << 2];
int MIN[maxn][25];

void update(int pos , int val){
  while(pos <= N){
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

void build(){ // build RMQ
  for(int i = 2; i <= N; ++i){
    logs[i] = logs[i / 2] + 1;
  }
  for(int i = 1; i <= N; ++i){
    if(stay[i]){
      MIN[i][0] = p[i];
    }
    else{
      MIN[i][0] = inf;
    }
  }
  for(int j = 1; j <= logs[N] + 1; ++j){
    for(int i = 1; i <= N; ++i){
      int len = (1 << (j - 1));
      if(i + len <= N){
        MIN[i][j] = min(MIN[i][j - 1] , MIN[i + len][j - 1]);
      }
      else{
        MIN[i][j] = MIN[i][j - 1];
      }
    }
  }
}

int min_query(int l , int r){
  if(l > r)return inf;
  int len = r - l + 1;
  return min(MIN[l][logs[len]] , MIN[r - (1 << logs[len]) + 1][logs[len]]);
}

int getleft(int pos){ // return minimal x such that a[x..pos] >= a[pos]
  int l = 1 , r = pos , x = pos;
  while(l <= r){
    int mid = (l + r) >> 1;
    if(min_query(mid , pos) >= p[pos]){
      x = mid;
      r = mid - 1;
    }
    else{
      l = mid + 1;
    }
  }
  return x;
}

int getright(int pos){ // return maximal x such that a[pos..x] >= a[pos]
  int l = pos , r = N , x = pos;
  while(l <= r){
    int mid = (l + r) >> 1;
    if(min_query(pos , mid) >= p[pos]){
      x = mid;
      l = mid + 1;
    }
    else{
      r = mid - 1;
    }
  }
  return x;
}

int main(){
  height[0] = maxn + 10;
  scanf("%d %d" , &N , &K);
  for(int i = 1; i <= N; ++i){
    scanf("%d" , &p[i]);
    mp[p[i]] = i; // mp[val] -> position in array
    update(i , 1);
  }
  for(int i = 1; i <= K; ++i){
    int x; scanf("%d" , &x);
    stay[mp[x]] = 1;
  }
  for(int i = 1; i <= N; ++i){
    if(!stay[mp[i]])re.push_back(mp[i]);
  }
  build();
  ll ans = 0;
  for(int i : re){ // remove from smallest to largest (in terms of value)
    int l = getleft(i); // binary search minimal l
    int r = getright(i); // binary search maximal r
    ans += ask(r) - ask(l - 1); // range sum query
    update(i , -1); // point update
  }
  printf("%lld\n" , ans);
}
