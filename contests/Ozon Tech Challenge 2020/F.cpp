#pragma GCC optimize(3)
#pragma GCC optimize(2)
#include <bits/stdc++.h>
#define DEBUG(x) std::cerr << #x << '=' << x << std::endl
using namespace std;
typedef long long ll;
typedef pair<int , int> ii;
mt19937_64 mt(chrono::steady_clock::now().time_since_epoch().count());

const int maxn = 2e5 + 10;
const int limit = 1e6 + 10;
const ll inf = 1e18;
int N;
ll a[maxn];
bool vis[limit];
unordered_set<int> ps;
unordered_set<ll> can;

/*
  random algorithm + greedy check
  very good problem!!!
  key is to notice that, ans <= N
  so there are at least N/2 elements getting changes for no more than 1
  in optimal solution, so we randomly shuffle N elements and pick the first k
  let x = a[k] , add all primes of (x + 1 , x , x - 1) into our candidate set
  probabilty of failing all k checks is 1 - (1 / 2) ^ k , when k large enough
  we are almost certain to get a correct solution
*/

void sieve(){
  for(int i = 2; i < limit; ++i){
    if(!vis[i]){
      ps.insert(i);
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
    ret = min(ret , (ll)N);
  }
  return ret;
}

void add(ll p){
  for(int i : ps){
    if(p % i == 0){
      can.insert(i);
      while(p % i == 0){
        p /= i;
      }
    }
  }
  /*for(ll i = 2; i * i <= p; ++i){
    if(p % i == 0){
      can.insert(i);
      while(p % i == 0){
        p /= i;
      }
    }
  }*/
  if(p > 1){
    can.insert(p);
  }
}

int main(){
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cin >> N;
  unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
  vector<int> id;
  for(int i = 1; i <= N; ++i){
    id.push_back(i);
    cin >> a[i];
  }
  sieve();
  //shuffle(id.begin() , id.end() , mt);
  shuffle(id.begin(), id.end(), std::default_random_engine(seed));
  for(int i = 0; i < 50 && i < id.size(); ++i){
    int x = id[i];
    add(a[x]);
    add(a[x] + 1);
    if(a[x] > 2)add(a[x] - 1);
  }
  ll ret = N;
  for(ll i : can){
    ret = min(ret , solve(i));
  }
  cout << ret << endl;
}
