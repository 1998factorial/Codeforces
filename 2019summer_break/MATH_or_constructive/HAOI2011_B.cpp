#include <iostream>
#include <algorithm>
using namespace std;

const int maxn = 5e4 + 10;
bool flag[maxn];
int mu[maxn];
int p[maxn];
int tot;

void init(){
  mu[1] = 1;
  for(int i = 2; i < maxn; ++i){
    if(!flag[i])p[++tot] = i , mu[i] = -1;
    for(int j = 1; j <= tot && i * p[j] < maxn; ++j){
      flag[i * p[j]] = 1;
      if(i % p[j] == 0){
        mu[i * p[j]] = 0;
        break;
      }
      mu[i * p[j]] = -mu[i];
    }
  }
  for(int i = 1; i < maxn; ++i)mu[i] += mu[i - 1];
}

int solve(int n , int m){
  int ret = 0;
  for(int i = 1 , j; i <= min(n , m); i = j + 1){
    j = min(n / (n / i) , m / (m / i));
    ret += (mu[j] - mu[i - 1]) * (n / i) * (m / i);
  }
  return ret;
}

int main(){
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  int T , a , b , c , d , k;
  init();
  cin >> T;
  while(T--){
    cin >> a >> b >> c >> d >> k;
    cout << solve(d / k , b / k) - solve(d / k , (a - 1) / k) - solve((c - 1) / k , b / k) + solve((c - 1) / k , (a - 1) / k) << endl;
  }
}
