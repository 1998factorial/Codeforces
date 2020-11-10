#include <bits/stdc++.h>
using namespace std;

const int maxn = 2e5 + 10;
char a[maxn];
int cnt[maxn][10];
int N;

void solve(){
  for(int i = N; i >= 1; --i){
    for(int j = a[i] - '0' - 1; j >= 0; --j){
      if(i == 1 && j == 0)continue;
      int odd = 0;
      for(int k = 0; k <= 9; ++k){
        if(k == j)odd += 1 - cnt[i - 1][k];
        else odd += cnt[i - 1][k];
      }
      if(odd <= N - i){
        for(int k = 1; k < i; ++k){
          printf("%c" , a[k]);
        }
        printf("%c" , '0' + j);
        for(int k = i + 1; k <= N - odd; ++k){
          printf("9");
        }
        for(int k = 9; k >= 0; --k){
          if(cnt[i - 1][k] ^ (j == k)){
            printf("%c" , '0' + k);
          }
        }
        printf("\n");
        return;
      }
    }
  }
  // if we can not find any
  for(int i = 1; i <= N - 2; ++i)printf("9");
  printf("\n");
}

int main(){
  int T;
  scanf("%d" , &T);
  while(T--){
    scanf("%s" , a + 1);
    N = strlen(a + 1);
    for(int i = 1; i <= N; ++i){
      int v = a[i] - '0';
      for(int j = 0; j <= 9; ++j){
        if(j == v)cnt[i][j] = 1 - cnt[i - 1][j];
        else cnt[i][j] = cnt[i - 1][j];
      }
    }
    solve();
  }
}
