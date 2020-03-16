#pragma GCC optimize(3)
#pragma GCC optimize(2)
#include <bits/stdc++.h>
#define DEBUG(x) std::cerr << #x << '=' << x << std::endl
using namespace std;
typedef long long ll;
typedef pair<int , int> ii;
const int maxn = 1e6 + 10;
char s[maxn];
int N;

int main(){
  scanf("%d" , &N);
  scanf("%s" , s + 1);
  int cnt = 0;
  for(int i = 1; i <= N; ++i){
    if(s[i] == ')')--cnt;
    else ++cnt;
  }
  if(cnt != 0){
    cout << -1 << endl;
    return 0;
  }
  int ans = 0;
  int pre = 1;
  bool bal = 1;
  for(int i = 1; i <= N; ++i){
    if(s[i] == '(')++cnt;
    else --cnt;
    if(bal){
      if(cnt == -1){
        pre = i;
        bal = 0;
        //cout << "unbalance at " << i << endl;
      }
    }
    else{
      if(cnt == 0){
        bal = 1;
        //cout << "balance at " << i << endl;
        ans += i - pre + 1;
        //cout << i - pre + 1 << endl;
      }
    }
    //printf("pre = %d\n" , pre);
  }
  printf("%d\n" , ans);
}
