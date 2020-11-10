#include <bits/stdc++.h>
using namespace std;

/*
  I currently do no understand the DP solution
  :(
*/


const int maxn = 2e5 + 10;
const int inf = 1e9 + 10;
int a[maxn];
int g[maxn] , f[maxn];
int N;

int main(){
  scanf("%d" , &N);
  for(int i = 1; i <= N; ++i)scanf("%d" , &a[i]) , f[i] = g[i] = inf;
  int ret = 0 , pos;
  for(int i = 2; i <= N; ++i){
    pos = upper_bound(g + 1 , g + 1 + N , a[i] - i + 1) - g;
    g[pos] = a[i] - i + 1;
    ret = max(ret , pos);
    pos = upper_bound(f + 1 , f + 1 + N , a[i - 1] - (i - 1)) - f;
    f[pos] = a[i - 1] - (i - 1);
    g[pos] = min(g[pos] , f[pos]);
    ret = max(ret , pos);
  }
  printf("%d\n" , N - ret - 1);
}
