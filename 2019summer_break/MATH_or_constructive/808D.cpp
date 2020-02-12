#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int maxn = 1e5 + 10;

int N;
ll a[maxn];
ll tot;

bool solve(){
  if(tot % 2 == 1)return 0;
  tot /= 2;
  ll tmp = tot;
  set<ll> vis;
  for(int i = 1; i <= N; ++i){
    vis.insert(a[i]);
    tot -= a[i];
    if(vis.count(-tot) || tot == 0){
      return 1;
    }
  }
  tot = tmp;
  vis.clear();
  for(int i = N; i >= 1; --i){
    vis.insert(a[i]);
    tot -= a[i];
    if(vis.count(-tot) || tot == 0){
      return 1;
    }
  }
  return 0;
}

int main(){
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cin >> N;
  tot = 0;
  for(int i = 1; i <= N; ++i){
    cin >> a[i];
    tot += a[i];
  }
  if(solve()){
    cout << "YES" << endl;
  }
  else{
    cout << "NO" << endl;
  }
}
