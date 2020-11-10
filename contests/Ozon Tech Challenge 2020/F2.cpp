#pragma GCC optimize(3)
#pragma GCC optimize(2)
#include <bits/stdc++.h>
#define DEBUG(x) std::cerr << #x << '=' << x << std::endl
using namespace std;
typedef long long ll;
typedef pair<int , int> ii;

/*
  TLE solution but still good solution
  notice that ans <= N, so if we pick some a[i]
  then in optimal solution, a[i] will be in ranges
  of [a[i] - N , a[i] + N]
  we can factorize all numbers in this range, and
  obtain a primes candidate set.
  for each of these primes, we can run a O(N) check
  O(N * sqrt(N) + log(maxa[i]) * N)
*/

const int maxn = 2e5 + 10;
const int limit = 1e6 + 10;
ll a[maxn];
int N;
bool vis[limit];
vector<int> ps;
unordered_set<ll> can;

void sieve(){
  for(int i = 2; i < limit; ++i){
    if(!vis[i]){
      ps.push_back(i);
      for(int j = i; j < limit; j += i){
        vis[j] = 1;
      }
    }
  }
}

ll solve(ll d){
  ll ret = 0;
  for(int i = 1; i <= N; ++i){
    ll t = a[i] < d ? d - a[i] : min(a[i] % d , d - a[i] % d);
    ret += t;
    if(ret > N)return N;
  }
  return ret;
}

void add(ll p){
  for(ll i = 2; i * i <= p; ++i){
    if(p % i == 0){
      can.insert(i);
      while(p % i == 0){
        p /= i;
      }
    }
  }
  if(p > 1){
    can.insert(p);
  }
}

int main(){
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cin >> N;
  //sieve();
  for(int i = 1; i <= N; ++i){
    cin >> a[i];
  }
  for(ll i = max(2ll , a[1] - N); i <= a[1] + N; ++i){
    add(i);
  }
  ll ret = N;
  for(ll i : can){
    ret = min(ret , solve(i));
  }
  cout << ret << endl;
}
