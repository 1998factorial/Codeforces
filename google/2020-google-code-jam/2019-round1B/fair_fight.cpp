#pragma GCC optimize(3)
#pragma GCC optimize(2)
#include <bits/stdc++.h>
#define DEBUG(x) std::cout << #x << '=' << x << std::endl
using namespace std;
typedef long long ll;
typedef pair<int , int> ii;

int T , N , K;
const int maxn = 1e5 + 10;
int MAX[maxn][25][2];
int A[maxn] , B[maxn];
int logs[maxn];

void build(){
  for(int i = 2; i <= N; ++i)
    logs[i] = logs[i / 2] + 1;
  for(int i = 1; i <= N; ++i){
    MAX[i][0][0] = A[i];
    MAX[i][0][1] = B[i];
  }
  for(int j = 1; j <= logs[N] + 1; ++j){
    for(int i = 1; i <= N; ++i){
      int len = (1 << (j - 1));
      if(i + len <= N){
        MAX[i][j][0] = max(MAX[i][j - 1][0] , MAX[i + len][j - 1][0]);
        MAX[i][j][1] = max(MAX[i][j - 1][1] , MAX[i + len][j - 1][1]);
      }
      else{
        MAX[i][j][0] = MAX[i][j - 1][0];
        MAX[i][j][1] = MAX[i][j - 1][1];
      }
    }
  }
}

int query(int l , int r , int which){
    int len = r - l + 1;
    return max(MAX[l][logs[len]][which] , MAX[r - (1 << logs[len]) + 1][logs[len]][which]);
}


int find_l(int pos , int val , int j){
  int ret = -1;
  int l = 1 , r = pos;
  while(l <= r){
    int mid = (l + r) >> 1;
    if(query(mid , pos , j) <= val){
      ret = mid;
      r = mid - 1;
    }
    else{
      l = mid + 1;
    }
  }
  return ret;
}

int find_r(int pos , int val , int j){
  int ret = -1;
  int l = pos , r = N;
  while(l <= r){
    int mid = (l + r) >> 1;
    if(query(pos , mid , j) <= val){
      ret = mid;
      l = mid + 1;
    }
    else{
      r = mid - 1;
    }
  }
  return ret;
}

void solve(){
  build();
  ll ret = 0;
  for(int i = 1; i <= N; ++i){
    int l1 = i , r1 = find_r(i , A[i] , 0); // avoid over counting
    int l = 1 , r = i - 1;
    while(l <= r){
      int mid = (l + r) >> 1;
      if(query(mid , i - 1 , 0) < A[i])l1 = mid , r = mid - 1;
      else l = mid + 1;
    }
    int l2 = find_l(i , A[i] + K , 1) , r2 = find_r(i , A[i] + K , 1);
    int l3 = find_l(i , A[i] - K - 1 , 1) , r3 = find_r(i , A[i] - K - 1 , 1);
    if(l2 == -1 || r2 == -1)continue;
    l = max(l1 , l2);
    r = min(r1 , r2);
    ret += (ll)(i - l + 1) * (ll)(r - i + 1);
    if(l3 != -1 && r3 != -1)
    ret -= (ll)(i - max(l3 , l) + 1) * (ll)(min(r3 , r) - i + 1);
  }
  cout << ret << endl;
}

int main(){
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cin >> T;
  for(int t = 1; t <= T; ++t){
    cin >> N >> K;
    for(int i = 1; i <= N; ++i){
      cin >> A[i];
    }
    for(int i = 1; i <= N; ++i){
      cin >> B[i];
    }
    cout << "Case #" << t << ": ";
    solve();
  }
}
