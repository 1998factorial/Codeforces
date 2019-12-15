#include <iostream>
#include <algorithm>
#include <vector>
#include <unordered_map>
using namespace std;
typedef long long ll;
const int maxn = 2e5 + 50;
int a[maxn] , b[maxn];

int main() {
  int n, m, k;
  cin >> n >> m >> k;
  for(int i = 0; i < n; ++i)cin >> a[i];
  for(int i = 0; i < n; ++i)b[i] = a[i];
  sort(a , a + n , [](int x , int y){
    return x > y;
  });
  unordered_map<int, int> cnt;
  ll ret = 0;
  for(int i = 0; i < m * k; ++i){
    ++cnt[a[i]];
    ret += a[i];
  }
  cout << ret << endl;
  int cur = 0;
  int j = 0;
  for(int i = 0; i < n; ++i){
    if(cnt[b[i]] > 0){
      ++cur;
      --cnt[b[i]];

    if(cur % m == 0 && j < k - 1){
      cout << i + 1 << " ";
      ++j;
    }
  }
  }
  cout << endl;
}
