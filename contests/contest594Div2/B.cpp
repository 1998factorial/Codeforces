#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <vector>
using namespace std;
typedef long long ll;
typedef pair<int , int > ii;

const int maxn = 3e5 + 10;
int N;
ll a[maxn];
ll sum[maxn];
int main(){
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cin >> N;
  sum[0] = 0;
  for(int i = 1; i <= N; ++i){
    cin >> a[i];
  }
  sort(a + 1 , a + N + 1);
  for(int i = 1; i <= N; ++i)sum[i] = sum[i - 1] + a[i];
  ll x = sum[N / 2];
  ll y = sum[N] - x;
  cout << x * x + y * y << endl;
  return 0;
}
