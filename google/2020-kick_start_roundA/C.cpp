#pragma GCC optimize(3)
#pragma GCC optimize(2)
#include <bits/stdc++.h>
#define DEBUG(x) std::cerr << #x << '=' << x << std::endl
using namespace std;
typedef long long ll;
typedef pair<int , int> ii;

const int maxn = 1e5 + 10;
int N , K;
int M[maxn];

bool check(int mid){
  int lim = K;
  for(int i = 2; i <= N; ++i){
    if(M[i] - M[i - 1] > mid){
      lim -= (M[i] - M[i - 1] - 1) / mid;
      if(lim < 0)return 0;
    }
  }
  return 1;
}


int solve(){
  scanf("%d %d" , &N , &K);
  for(int i = 1; i <= N; ++i){
    scanf("%d" , &M[i]);
  }
  int l = 1 , r = M[N] , ans = M[N];
  while(l <= r){
    int mid = (l + r) >> 1;
    if(check(mid)){
      ans = mid;
      r = mid - 1;
    }
    else{
      l = mid + 1;
    }
  }
  return ans;
}

int main(){
  int t; scanf("%d" , &t);
  for(int x = 1; x <= t; ++x){
    printf("Case #%d: %d\n" , x , solve());
  }
}
