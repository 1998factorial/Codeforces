#pragma GCC optimize(3)
#pragma GCC optimize(2)
#include <bits/stdc++.h>
#define DEBUG(x) std::cerr << #x << '=' << x << std::endl
using namespace std;
typedef long long ll;
typedef pair<int , int> ii;

const int maxn = 1e5 + 10;
int N;
int a[maxn];
int power_of_two[maxn];
vector<int> b;

void solve1(){
  if(N % 2){
    printf("NO\n");
  }
  else{
    printf("YES\n");
    int y = 1;
    while((y << 1) <= N) y <<= 1;
    int t = y;
    for(int i = N; i >= 1; i--) {
        if(t > i) t >>= 1;
          if(!a[i]) {
              int x = t - (i - t) - 1;
              a[i] = x;
              a[x] = i;
          }
        }
    for(int i = 1; i <= N; i++) {
        printf("%d ", a[i]);
    }
    printf("\n");
  }
}

bool get(int M){
  do{
    bool ok = 1;
    for(int i = 1; i <= M && ok; ++i){
      if(a[i] == i || (a[i] & i) == 0){
        ok = 0;
      }
    }
    if(ok){
      return 1;
    }
  }
  while(next_permutation(a + 1 , a + M + 1));
  return 0;
}

void solve2(){
  if(power_of_two[N]){
    printf("NO\n");
    return;
  }
  for(int i = 1; i <= N; ++i){
    a[i] = i;
  }
  if(N <= 7){
    if(get(N)){
      printf("YES\n");
      for(int i = 1; i <= N; ++i){
        printf("%d " , a[i]);
      }
      return;
    }
    else{
      printf("NO\n");
    }
  }
  else{
    printf("YES\n");
    get(7);
    for(int i = 1; i <= 7; ++i){
      printf("%d " , a[i]);
    }
    for(int k = 3; k < b.size() && b[k] <= N; ++k){
      int limit = N;
      if(k < b.size())limit = min(limit , b[k + 1] - 1);
      for(int i = b[k]; i <= limit; ++i){
        // generate for these a[2^k .. 2^(k+1) - 1]
        printf("%d " , limit - i + b[k]);
      }
    }
  }
}

int main(){
  scanf("%d" , &N);
  for(int i = 1; i < maxn; i <<= 1){
    b.push_back(i);
    power_of_two[i] = 1;
  }
  solve1();
  //solve2();
  if(power_of_two[N] || N < 6) puts("NO");
    else {
        puts("YES");
        if(N == 6) puts("3 6 2 5 1 4");
        else {
            printf("7 3 6 5 1 2 4 ");
            for(int i = 8; i <= N; ) {
                int j = min(i << 1, N + 1);
                for(int k = i; k < j - 1; k++) printf("%d ", k+1);
                printf("%d ", i);
                i = j;
            }
        }
    }
}
