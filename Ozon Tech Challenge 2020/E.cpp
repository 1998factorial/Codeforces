#pragma GCC optimize(3)
#pragma GCC optimize(2)
#include <bits/stdc++.h>
#define DEBUG(x) std::cerr << #x << '=' << x << std::endl
using namespace std;
typedef long long ll;
typedef pair<int , int> ii;

int N , M;
int sum[5005];
int ans[5005];

int main(){
  scanf("%d %d" , &N , &M);
  for(int i = 1; i <= N; ++i){
    sum[i] = sum[i - 1] + (i - 1) / 2;
  }
  int c = 0;
  for(int i = 1; i <= N; ++i){
    if(sum[i] <= M)c = i;
  }
  if(c == N){
    if(M > sum[N]){
      printf("-1\n");
      return 0;
    }
    if(M == sum[N]){
      for(int i = 1; i <= N; ++i)ans[i] = i;
    }
  }
  else{
    for(int i = 1; i <= c; ++i){
      ans[i] = i;
    }
    ans[c + 1] = 2 * c - 2 * (M - sum[c]) + 1;
    for(int i = c + 2; i <= N; ++i){
      ans[i] = 1e8 + (1e4) * i;
    }
  }
  for(int i = 1; i <= N; ++i)printf("%d ", ans[i]);
  printf("\n");
}
