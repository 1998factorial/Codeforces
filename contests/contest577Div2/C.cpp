#include <iostream>
#include <cstring>
#include <cstdio>
#include <algorithm>
using namespace std;
typedef long long ll;
const int maxn = 2e5 + 10;
int n,k;
ll a[maxn],sum[maxn];

int main(){
  cin >> n >> k;
  sum[0] = 0;
  for(int i = 1; i <= n; ++i){
    cin >> a[i];
  }
  sort(a+1,a+1+n);
  for(int i = 1; i <= n; ++i)
    sum[i] = sum[i - 1] + a[i];
  int start = (n + 1) / 2;
  ll ret = a[start];
  int cur = 0;
  int i = start;
  for(; i <= n; ++i){
    // check if (i - start) * a[i] - (sum[i] - sum[start - 1]) <= k
    if((i - start + 1) * a[i] - (sum[i] - sum[start - 1]) > k)break;
    cur = (i - start + 1) * a[i] - (sum[i] - sum[start - 1]);
    ret = a[i];
    //cout << i << "   " << cur << "   " << (i - start + 1) * a[i] << "   " << (sum[i] - sum[start - 1]) << endl;
    //cout << ret << endl;
  }
  ret += (k - cur) / (i - start);
  cout << ret << endl;
}
