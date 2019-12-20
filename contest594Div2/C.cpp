#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <vector>
using namespace std;
typedef long long ll;
typedef pair<int , int > ii;
const ll mod = 1e9 + 7;
const int maxn = 3e5 + 10;
int M , N;
ll F[maxn];

int main(){
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cin >> N >> M;
  F[0] = F[1] = 1;
  for(int i = 2; i <= max(N , M); ++i)F[i] = (F[i - 1] + F[i - 2] + mod) % mod;
  cout << (2ll * (F[N] + F[M] - 1) % mod + mod) % mod << endl;
  return 0;
}
