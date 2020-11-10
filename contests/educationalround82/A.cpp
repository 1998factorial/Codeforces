#pragma GCC optimize(3)
#pragma GCC optimize(2)
#include <bits/stdc++.h>
#define DEBUG(x) std::cerr << #x << '=' << x << std::endl
using namespace std;
typedef long long ll;
typedef pair<int , int> ii;

const int maxn = 105;
char s[maxn];


int main(){
  int T; scanf("%d" , &T);
  for(int t = 1; t <= T; ++t){
    scanf("%s" , s + 1);
    int N = strlen(s + 1);
    int l = -1 , r = -1;
    int cnt = 0;
    for(int i = 1; i <= N; ++i){
      if(s[i] == '1')++cnt;
      if(cnt == 1 && s[i] == '1'){
        l = i;
      }
      if(s[i] == '1'){
        r = i;
      }
    }
    if(l != -1)printf("%d\n" , r - l + 1 - cnt);
    else printf("0\n");
  }
}
