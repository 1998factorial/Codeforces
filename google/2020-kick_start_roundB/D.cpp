#pragma GCC optimize(3)
#pragma GCC optimize(2)
#include <bits/stdc++.h>
#define DEBUG(x) std::cerr << #x << '=' << x << std::endl
using namespace std;
typedef long long ll;
typedef pair<int , int> ii;

const int maxn = 2e5 + 10;
int N , M , L , U , R , D;
double logs[maxn];

double cal(int n , int r){
  double ret = 0;
  for(int i = 0; i < r; ++i){
    double t = logs[n] - logs[n - i] - logs[i] - n;
    ret += pow(2.0 , t);
  }
  return ret;
}

void solve(){
  scanf("%d %d %d %d %d %d" , &N , &M , &L , &U , &R , &D);
  double ret = 0;
  int n1 = L + D - 2 , n2 = R + U - 2 , r1 = L - 1 , r2 = U - 1;
  if(N == R)r2 = 0;
  if(M == D)r1 = 0;
  ret = cal(n1 , r1) + cal(n2 , r2);
  printf("%.12lf\n" , ret);
}

int main(){
  logs[0] = 0;
  for(int i = 1; i < maxn; ++i){
    logs[i] = logs[i - 1] + log2(i);
  }
  int T; scanf("%d" , &T);
  for(int t = 1; t <= T; ++t){
    printf("Case #%d: " , t);
    solve();
  }
}
