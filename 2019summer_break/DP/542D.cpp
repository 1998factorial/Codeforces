#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

/*
  J(a^x) = 1 + a^x
  X = (a)^x * (b)^y * (c)^z
  J(X) = (1 + a^x) * (1 + b^y) * (1 + c^z)
  task : given A , how many ways are there to obtain (1 + a^x) * (1 + b^y) * (1 + c^z) * ... = A ?
  can use DP
  find all divisors of A (not more than 1e4 for A <= 1e12)
  for each divisors d , for each prime p not greater than sqrt(A)
    if(d - 1 == p ^ k) this means p can contribute to A
  then we just do DP
  dp[i][j] = number of ways to use first i good primes to obtain the j-th divisors of A
  (divisors need to be sorted in ascending order)
*/


const int maxn = 1e6 + 10;
ll N;
ll divisors[10000];
ll primes[maxn]; // primes not greater than sqrt(A)
bool vis[maxn];
int cnt = 0; // number of divisors of N
int tot = 0; // number of primes
int cntgood = 0;
ll good_primes[10000];
unordered_map<ll , ll> mp;
ll dp[maxn];


void get_primes(ll M){
  for(ll i = 2; i <= M; ++i){
    if(!vis[i]){
      primes[++tot] = i;
      for(ll j = i; j <= M; j += i){
        vis[j] = 1;
      }
    }
  }
}

void check_divisors(ll M){
  for(ll i = 1; i * i <= M; ++i){
    if(M % i == 0){
      divisors[++cnt] = i;
      if(M / i != i)
        divisors[++cnt] = M / i;
    }
  }
  sort(divisors + 1 , divisors + cnt + 1);
  for(int i = 1; i <= cnt; ++i)
    mp[divisors[i]] = i;
}

void preprocess(){
  for(int i = 1; i <= cnt; ++i){
    ll tmp = divisors[i] - 1;
    for(int j = 1; j <= tot && primes[j] * primes[j] <= tmp; ++j ){
      if(tmp % primes[j] == 0){
        while(tmp % primes[j] == 0)tmp /= primes[j];
        if(tmp == 1)good_primes[++cntgood] = primes[j];
        break;
      }
    }
    if(tmp == divisors[i] - 1 && tmp > 1){
      good_primes[++cntgood] = tmp;
    }
  }
  sort(good_primes + 1 , good_primes + 1 + cntgood);
  cntgood = unique(good_primes + 1 , good_primes + 1 + cntgood) - good_primes - 1;
}

ll solve(){
  dp[1] = 1;
  for(int j = 1; j <= cntgood; ++j){
    for(int i = cnt; i >= 1; --i){
      for(ll t = good_primes[j]; t <= divisors[i]; t *= good_primes[j]){
        if(divisors[i] % (1 + t) == 0){
          dp[i] += dp[mp[divisors[i] / (1 + t)]];
        }
      }
    }
  }
  return dp[cnt];
}

int main(){
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cin >> N;
  check_divisors(N);
  get_primes(sqrt(N));
  preprocess();
  cout << solve() << endl;
}
