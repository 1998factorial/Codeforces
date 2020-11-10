#include <iostream>
#include <unordered_map>
#include <vector>
using namespace std;
typedef long long ll;

const int maxn = 8005;
int n;
ll a[maxn] , b[maxn];
int cnt;

int main(){
  cin >> n;
  for(int i = 1; i <= n; ++i){
    cin >> a[i];
  }
  for(int i = 1; i <= n; ++i){
    cin >> b[i];
  }
  unordered_map<ll , ll> mp;
  unordered_map<ll , ll> cnt;
  for(int i = 1; i <= n; ++i){
    mp[a[i]] += b[i];
    ++cnt[a[i]];
  }
  ll ret = 0;
  vector<ll> state;
  for(auto& it : cnt){
    if(it.second > 1){
      ret += mp[it.first];
      state.push_back(it.first);
      //mp.erase(it.first);
      mp[it.first] = 0;
    }
  }
  for(ll k : state){
    for(auto& i : mp){
      ll j = i.first;
      if((k & j) == j){
        ret += i.second;
        mp[j] = 0;
      }
    }
  }
  cout << ret << endl;
  return 0;
}
