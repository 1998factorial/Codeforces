#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int mod = 1e9 + 7;

char s[105];
int N , X;
int dp[105][105][105];
int len[105];
int power2[105];

ll add(ll a , ll b){
  return (a + b) % mod;
}

ll mul(ll a , ll b){
  return a * b % mod;
}

ll qpow(ll x , ll n){
  if(n <= 0)return 1;
  ll ret = qpow(x , n / 2);
  ret = mul(ret , ret);
  if(n & 1)ret = mul(ret , x);
  return ret;
}

int main(){
  scanf("%d %d" , &N , &X);
  scanf("%s" , s + 1);
  len[0] = len[1] = 1;
  for(int i = 2; i <= 100; ++i){
    len[i] = (len[i - 1] + len[i - 2]) % (mod - 1);
  }
  for(int i = 0; i <= 100; ++i){
    power2[i] = qpow(2ll , len[i]);
  }
  for(int i = 1; i <= N; ++i){
    dp[0][i][i] = s[i] == '0';
    dp[1][i][i] = s[i] == '1';
  }
  for(int i = 2; i <= X; ++i){
    for(int len = 1; len <= N; ++len){
      for(int l = 1; l + len - 1 <= N; ++l){
        int r = l + len - 1;
        if(r == N)dp[i][l][r] = add(dp[i][l][r] , mul(dp[i - 1][l][r] , power2[i - 2]));
        else dp[i][l][r] = add(dp[i][l][r] , dp[i - 1][l][r]);
        if(l == 1)dp[i][l][r] = add(dp[i][l][r] , mul(dp[i - 2][l][r] , power2[i - 1]));
        else dp[i][l][r] = add(dp[i][l][r] , dp[i - 2][l][r]);
        for(int k = l; k < r; ++k){
          dp[i][l][r] = add(dp[i][l][r] , mul(dp[i - 1][l][k] , dp[i - 2][k + 1][r]));
        }
      }
    }
  }
  printf("%d\n" , (dp[X][1][N] + mod) % mod);
}
