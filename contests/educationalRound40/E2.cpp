#pragma GCC optimize(3)
#pragma GCC optimize(2)
#include <bits/stdc++.h>
#define DEBUG(x) std::cerr << #x << '=' << x << std::endl
using namespace std;
typedef long long ll;
typedef pair<int , int> ii;

const int maxn = 2e5 + 10;
int N;
double T;
double a[maxn] , t[maxn];

double solve(){
  double Sp = 0 , Sn = 0 , ret = 0;
  vector<int> id;
  for(int i = 1; i <= N; ++i){
    id.push_back(i);
    if(t[i] > T){
      Sp += a[i] * (t[i] - T);
    }
    if(t[i] < T){
      Sn += a[i] * (T - t[i]);
    }
  }
  double goal = min(Sp , Sn);
  Sp = Sn = goal;
  sort(id.begin() , id.end() , [&](int x , int y){
    return abs(t[x] - T) < abs(t[y] - T);
  });
  for(int i : id){ // for positive group
    if(t[i] > T){
      double take = min(a[i] , Sp / (t[i] - T));
      Sp -= take * (t[i] - T);
      ret += take;
    }
  }
  for(int i : id){ // for negative group
    if(t[i] < T){
      double take = min(a[i] , Sn / (T - t[i])); // the maximal allowed x[i] for (T - t[i])
      Sn -= take * (T - t[i]); 
      ret += take;
    }
  }
  for(int i : id){
    if(t[i] == T)ret += a[i];
  }
  return ret;
}

int main(){
  scanf("%d %lf" , &N , &T);
  for(int i = 1; i <= N; ++i){
    scanf("%lf" , &a[i]);
  }
  for(int i = 1; i <= N; ++i){
    scanf("%lf" , &t[i]);
  }
  printf("%lf\n" , solve());
}
