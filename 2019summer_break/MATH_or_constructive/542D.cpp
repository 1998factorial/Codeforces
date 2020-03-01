#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int maxn = 1e6 + 10;
ll A;
ll primes[maxn];
ll good_primes[maxn];
ll divi[maxn];
bool vis[maxn];
ll dp[2][maxn];
int pcnt = 0;
int dcnt = 0;
int gpcnt = 0;
unordered_map<ll , int> mp;

void get_primes(ll N){
  for(ll i = 2; i <= N; ++i){
    if(!vis[i]){
      primes[++pcnt] = i;
      for(ll j = i; j <= N; j += i)vis[j] = 1;
    }
  }
}

void get_divisors(){
  for(ll i = 1; i * i <= A; ++i){
    if(A % i == 0){
      divi[++dcnt] = i;
      if(A / i != i){
        divi[++dcnt] = A / i;
      }
    }
  }
  sort(divi + 1 , divi + 1 + dcnt);
  for(int i = 1; i <= dcnt; ++i)mp[divi[i]] = i;
}

void get_good_primes(){
  for(int i = 1; i <= dcnt; ++i){
    ll t = divi[i] - 1;
    for(int j = 1; j <= pcnt && primes[j] * primes[j] <= t; ++j){
      if(t % primes[j] == 0){
        while(t % primes[j] == 0)t /= primes[j];
        if(t == 1)good_primes[++gpcnt] = primes[j];
        break;
      }
    }
    if(t == divi[i] - 1 && t > 1)//t is prime
      good_primes[++gpcnt] = t;
  }
  sort(good_primes + 1 , good_primes + 1 + gpcnt);
  gpcnt = unique(good_primes + 1 , good_primes + 1 + gpcnt) - good_primes - 1;
}

ll solve(){
  dp[0][1] = 1;
  for(int i = 1; i <= gpcnt; ++i){
    for(int j = 1; j <= dcnt; ++j){
      dp[i & 1][j] = dp[(i - 1) & 1][j];
      for(ll t = good_primes[i]; t <= divi[j]; t *= good_primes[i]){
        if(divi[j] % (1 + t) == 0){
          dp[i & 1][j] += dp[(i - 1) & 1][mp[divi[j] / (1 + t)]];
        }
      }
    }
  }
  return dp[gpcnt & 1][dcnt];
}

int main(){
  cin >> A;
  get_primes(sqrt(A));
  get_divisors();
  get_good_primes();
  cout << solve() << endl;
}
