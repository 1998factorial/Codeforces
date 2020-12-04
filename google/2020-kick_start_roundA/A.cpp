#pragma GCC optimize(3)
#pragma GCC optimize(2)
#include <bits/stdc++.h>
#define DEBUG(x) std::cerr << #x << '=' << x << std::endl
using namespace std;
typedef long long ll;
typedef pair<int , int> ii;

const int maxn = 1e5 + 10;
int N , B;
int A[maxn];

int solve(){
  scanf("%d %d" , &N , &B);
  for(int i = 1; i <= N; ++i){
    scanf("%d" , &A[i]);
  }
  sort(A + 1 , A + 1 + N);
  int ret = 0;
  int S = 0;
  for(int i = 1; i <= N; ++i){
    S += A[i];
    if(S <= B)ret = i;
  }
  return ret;
}

int main(){
  int t; scanf("%d" , &t);
  for(int x = 1; x <= t; ++x){
    printf("Case #%d: %d\n" , x , solve());
  }
}
