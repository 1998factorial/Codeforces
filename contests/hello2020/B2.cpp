#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
typedef long long ll;

const int inf = 1e9;
const int maxn = 1e5 + 10;
int N;
vector<int> a[maxn];
bool yes[maxn];

int main(){
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cin >> N;
  for(int i = 1; i <= N; ++i){
    int len; cin >> len;
    int pre = inf;
    for(int j = 1; j <= len; ++j){
      int x;cin >> x;a[i].push_back(x);
      if(pre < x)yes[i] = 1;
      pre = min(pre , x);
    }
  }
  ll ret = 0;
  for(int i = 1; i <= N; ++i){
    for(int j = 1; j <= N; ++j){
      if(yes[i] || yes[j])++ret;
      else{
        int mn = inf , mx = -1;
        for(int k : a[i]){
          mn = min(k , mn);
        }
        for(int k : a[j]){
          mx = max(mx , k);
        }
        if(mn < mx)++ret;
      }
    }
  }
  cout << ret << endl;
}
