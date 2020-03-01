#include <bits/stdc++.h>
using namespace std;

const int maxn = 2e5 + 10;
const double ep = 1e-6;

struct tap{
  double a , t;
  tap(){}
  tap(double x , double y) : a(x) , t(y) {}
  bool operator < (const tap& rhs) const {
    return t < rhs.t;
  }
}s[maxn];

int N;
double T;

double solve(){
  double l = 0 , r = 0 , ret = 0;
  for(int i = 1; i <= N; ++i)r += s[i].a;
  for(int i = 1; i <= 50; ++i){ //100 times of binary search on amount of water
    double mid = (l + r) / 2;
    double t1 = 0 , t2 = 0 , total = mid , t = mid * T;
    for(int j = 1; j <= N && total > 0; ++j){
      double take = s[j].a;
      take = min(take , total);
      t1 += s[j].t * take;
      total -= take;
    }
    total = mid;
    for(int j = N; j >= 1 && total > 0; --j){
      double take = s[j].a;
      take = min(take , total);
      t2 += s[j].t * take;
      total -= take;
    }
    if(t - t1 > -ep && t - t2 < ep){
      ret = mid;
      l = mid;
    }
    else{
      r = mid;
    }
  }
  return ret;
}

int main(){
  scanf("%d %lf" , &N , &T);
  for(int i = 1; i <= N; ++i){
    scanf("%lf" , &s[i].a);
  }
  for(int i = 1; i <= N; ++i){
    scanf("%lf" , &s[i].t);
  }
  sort(s + 1 , s + 1 + N);
  printf("%lf\n" , solve());
}
