#include <bits/stdc++.h>
using namespace std;

/*
if we can finish the game with the current cards, then just finish it with minimal steps
else we can play out all empty cards and finish the game with extra N steps
*/

const int maxn = 2e5 + 10;
int a[maxn] , b[maxn] , pos[maxn];
int N;

int solve(){
  int ret = 0;
  if(pos[1]){
    int i = 2;
    for(; i <= N && pos[i] == pos[i - 1] + 1; ++i);
    if(pos[i - 1] == N){
      int j = i;
      for(; j <= N && pos[j] < j - i + 1; ++j);
      if(j > N)return N - (i - 1);
    }
  }
  for(int i = 1; i <= N; ++i){
    ret = max(ret , pos[i] + 1 + (N - i));
  }
  return ret;
}

int main(){
  cin >> N;
  for(int i = 1; i <= N; ++i)
    cin >> a[i];
  for(int i = 1; i <= N; ++i){
    cin >> b[i];
    pos[b[i]] = i;
  }
  cout << solve() << endl;
}
