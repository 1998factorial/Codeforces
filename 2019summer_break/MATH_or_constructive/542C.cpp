#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

/*
  find minmal k such that f(k) (f(k) (x)) = f(k)(x)
  where f(1)(x) = f(x) , f(k)(x) = f(f(k - 1)(x))

  path of transition looks like a linked list (could be empty) to a cycle

  let lengths of cycles be k1 , k2 , .. , kn
  k must be a multiple of lcm(k1 , k2 , ... , kn)
  and it must be at least max{ length(linked list to cycle) }

*/

int N;
int F[205];
ll len[205];
ll vis[205];

ll gcd(ll a , ll b){
  return a == 0 ? b : gcd(b % a , a);
}

ll lcm(ll a , ll b){
  return a * b / gcd(a , b);
}

int main(){
  cin >> N;
  for(int i = 1; i <= N; ++i){
    cin >> F[i];
  }
  ll max_to_cycle = 0;
  for(int x = 1; x <= N; ++x){
    for(int j = 1; j <= N; ++j)vis[j] = 0;
    ll cnt = 0;
    int y = x;
    while(!vis[F[y]]){
      vis[F[y]] = ++cnt;
      y = F[y];
    }
    max_to_cycle = max(max_to_cycle , vis[F[y]]); // length to cycle
    len[x] = cnt - vis[F[y]] + 1; // cycle length
  }
  ll LCM = len[1];
  for(int i = 2; i <= N; ++i){
    LCM = lcm(LCM , len[i]);
  }
  ll ret = LCM;
  while(ret < max_to_cycle)ret += LCM;
  cout << ret << endl;
}
