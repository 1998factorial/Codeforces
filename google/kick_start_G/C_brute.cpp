#pragma GCC optimize(3)
#pragma GCC optimize(2)
#include <bits/stdc++.h>
#define DEBUG(x) std::cerr << #x << '=' << x << std::endl
using namespace std;
typedef long long ll;
typedef pair<int , int> ii;
typedef unsigned long long ull;

const int maxn = 20;
int N , H;
int A[maxn] , B[maxn];
const ll maxS = 3486784401;

// convert into base 3
// ith number = 0 -> only A , 1 -> only B , 2 -> A and B

int solve(){
  int ret = 0;
  ll up = 1;
  for(int i = 1; i <= N; ++i)up *= 3ll;
  for(ll s = 0; s < up; ++s){
    // compute
    ll vA = 0 , vB = 0;
    vector<int> mask;
    ll n = s;
    while(n){
      mask.push_back(n % 3);
      n /= 3ll;
    }
    for(int i = mask.size(); i < N; ++i){
      mask.push_back(0);
    }
    for(int i = 0; i < N; ++i){
      if(mask[i] == 0)vA += A[i];
      if(mask[i] == 1)vB += B[i];
      if(mask[i] == 2)vA += A[i] , vB += B[i];
    }
    if(vA >= H && vB >= H)++ret;
  }
  return ret;
}

int main(){
  int T; scanf("%d" , &T);
  for(int t = 1; t <= T; ++t){
    scanf("%d %d" , &N , &H);
    for(int i = 0; i < N; ++i){
      scanf("%d" , &A[i]);
    }
    for(int i = 0; i < N; ++i){
      scanf("%d" , &B[i]);
    }
    printf("Case #%d: %d\n" , t , solve());
  }
}
