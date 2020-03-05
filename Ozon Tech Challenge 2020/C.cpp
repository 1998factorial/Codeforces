#pragma GCC optimize(3)
#pragma GCC optimize(2)
#include <bits/stdc++.h>
#define DEBUG(x) std::cerr << #x << '=' << x << std::endl
using namespace std;
typedef long long ll;
typedef pair<int , int> ii;

const int maxn = 2e5 + 10;
int N , M;
ll a[maxn];
ll cnt[1005];

int main(){
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cin >> N >> M;
  for(int i = 1; i <= N; ++i){
    cin >> a[i];
  }
  sort(a + 1 , a + 1 + N);
  ll ret = (a[2] - a[1]) % M;
  cnt[a[2] % M]++;
  cnt[a[1] % M]++;
  for(int i = 3; i <= N && ret; ++i){
    for(int j = 0; j < M && ret; ++j){
      if(cnt[j] == 0)continue;
      ll t = cnt[j] * (a[i] - j) % M;
      ret = ret * t % M;
    }
    cnt[a[i] % M]++;
  }
  cout << (ret + M) % M << endl;
}
