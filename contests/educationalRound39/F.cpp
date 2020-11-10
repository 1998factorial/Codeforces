#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

/*
  dp[i][l][r] = "total number of times for s[l .. r] to appear in all subsequences of F[i]"
  F[i] = F[i - 1] concat F[i - 2]
  to get dp[i][l][r] from dp[0 .. i - 1][1 .. N][1 .. N]
  we consider on merging solution for F[i - 1] and F[i - 2]
  if r == N , we fix s[l .. r] in subsequences in F[i - 1] , and we can choose any subseq from F[i - 2]
  similarly , if l == 1, we fix s[l .. r] in F[i - 2] , we can choose any subseq in F[i - 1]
  if r < N , to not match any s[l ... k] st k > r , we only want dp[i - 1][l][r]
  similarly , if l > 1 , we only want dp[i - 2][l][r]
  F[i - 1] can have s[l .. k] and F[i - 2] can have s[k + 1 .. r]
  thus , ways = dp[i - 1][l][k] * dp[i - 2][k + 1][r] for l <= k <= r
  solution will be dp[X][1][N]
*/

const ll mod = 1e9 + 7;
int N , X;
char s[105];
ll len[105];
ll pt[105];
ll dp[105][105][105];
bool vis[105][105][105];

ll add(ll a , ll b){
  return (a + b) % mod;
}

ll mul(ll a , ll b){
  return a * b % mod;
}

ll qpow(ll a , ll n){
  if(n <= 0)return 1ll;
  ll ret = qpow(a , n / 2);
  ret = mul(ret , ret);
  if(n % 2)ret = mul(ret , a);
  return ret;
}

ll solve(int i , int l , int r){
  if(i == 0)return (l == r) && s[l] == '0';
  if(i == 1)return (l == r) && s[l] == '1';
  if(vis[i][l][r])return dp[i][l][r];
  vis[i][l][r] = 1;
  ll ret = 0;
  if(r == N)
    ret = add(ret , mul(solve(i - 1 , l , r) , pt[i - 2]));
  else
    ret = add(ret , solve(i - 1 , l , r));
  if(l == 1)
    ret = add(ret , mul(solve(i - 2 , l , r) , pt[i - 1]));
  else
    ret = add(ret , solve(i - 2 , l , r));
  for(int k = l; k <= r; ++k){
    ret = add(ret , mul(solve(i - 1 , l , k) , solve(i - 2 , k + 1 , r)));
  }
  dp[i][l][r] = ret;
  return dp[i][l][r];
}


int main(){
  scanf("%d %d" , &N , &X);
  scanf("%s" , s + 1);
  len[0] = len[1] = 1;
  for(int i = 2; i <= 100; ++i)
    len[i] = (len[i - 1] + len[i - 2] + mod - 1) % (mod - 1);
  for(int i = 0; i <= 100; ++i){
    pt[i] = qpow(2ll , len[i]);
  }
  printf("%lld\n" , add(solve(X , 1 , N) , mod));
}
