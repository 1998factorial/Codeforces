#include <iostream>
#include <cstring>
#include <string.h>
using namespace std;

const int maxn = 1e5 + 10;
int cnt[maxn][26];
int N , Q;
string a;

int check(int l , int r){ // palindrome -> all even, or exactly one odd
  int num = 0;
  for(int i = 0; i < 26; ++i)
    num += (cnt[r][i] - cnt[l][i]) % 2 == 1;
  return num <= 1;
}

int solve(){
  int ret = 0;
  for(int q = 1; q <= Q; ++q){
    int l , r;
    cin >> l >> r;
    ret += check(l - 1 , r);
  }
  return ret;
}

void preprocess(){
  memset(cnt , 0 , sizeof(cnt));
  for(int i = 1; i <= N; ++i){
    for(int j = 0; j < 26; ++j)cnt[i][j] = cnt[i - 1][j];
    ++cnt[i][a[i - 1] - 'A'];
  }
}

int main(){
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  int T;
  cin >> T;
  for(int t = 1; t <= T; ++t){
    cin >> N >> Q;
    cin >> a;
    preprocess();
    cout << "Case #" << t << ": " << solve() << endl;
  }
  return 0;
}
