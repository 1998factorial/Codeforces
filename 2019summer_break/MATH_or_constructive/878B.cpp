#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<ll , ll> ii;

int N , K , M;

int main(){
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cin >> N >> K >> M;
  vector<ii> a;
  for(int i = 1; i <= N; ++i){
    int x; cin >> x;
    if(a.empty()){
      a.emplace_back(x , 1);
    }
    else if(a.back().first == x){
      a.back().second++;
    }
    else{
      a.emplace_back(x , 1);
    }
    if(a.back().second == K){
      a.pop_back();
    }
  }
  int n = a.size();
  int l = 0 , r = n - 1;
  ll len1 = 0 , len2 = 0 , ret = 0;
  for(int i = 0; i < n; ++i)len1 += a[i].second;
  while(l < r && a[l].first == a[r].first && (a[l].second + a[r].second) % K == 0){
    len2 += a[l].second + a[r].second , ++l , --r;
  }
  if(l == r){
    if(a[l].second * M % K == 0){
      ret = len1 * M - len2 * M - (a[l].second * M / K * K);
    }
    else{
      ret = len1 * M - len2 * (M - 1) - (a[l].second * M / K * K);
    }
    // ret = len1 * M - len2 * (M - 1) - (a[l].second * M - a[l].second * M % K)
  }
  else{
    if(a[l].first == a[r].first){
      len2 += (a[l].second + a[r].second) / K * K;
    }
    ret = len1 * M - len2 * (M - 1);
  }
  cout << ret << endl;
}
