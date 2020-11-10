#include <iostream>
#include <cstring>
#include <cstdio>
#include <algorithm>
using namespace std;
typedef long long ll;
const int maxn = 1e5 + 10;
int n;
ll a[maxn];
// S' = S - 2
// max of a[] has to be <= the combine of the rest of elem
bool solve(){
  ll sum = 0;
  int mx = -1;
  for(int i = 1; i <= n; ++i){
    sum += a[i];
    mx = max((ll)mx , a[i]);
  }
  if(sum % 2)return false;
  if(mx > sum - mx) return false;
  return true;
}

int main(){
  cin >> n;
  for(int i = 1; i <= n; ++i)cin >> a[i];
  if(solve())cout << "YES\n";
  else cout << "NO\n";
}
