#include <bits/stdc++.h>
using namespace std;

/*
  I had no idea about how to do this problem at first :(
  later I bow to the solution


*/

const int maxn = 2e5 + 10;
double a[maxn] , t[maxn];
int N;
double T;

int main(){
  vector<int> ord;
  scanf("%d %lf" , &N , &T);
  for(int i = 1; i <= N; ++i){
    scanf("%lf" , &a[i]);
  }
  for(int i = 1; i <= N; ++i){
    scanf("%lf" , &t[i]);
    ord.push_back(i);
  }
  // group taps into negative / positive group
  double Sn = 0 , Sp = 0;
  for(int i = 1; i <= N; ++i){
    if(t[i] > T)
      Sp += a[i] * (t[i] - T);
    if(t[i] < T)
      Sn += a[i] * (T - t[i]);
  }
  sort(ord.begin() , ord.end() , [&](int x , int y){
    return abs(t[x] - T) < abs(t[y] - T);
  });
  double S = min(Sn , Sp) , ret = 0;
  Sn = Sp = S;
  for(int i : ord){
    if(t[i] > T){
      double take = min(a[i] , Sp / (t[i] - T));
      Sp -= take * (t[i] - T);
      ret += take;
    }
  }
  for(int i : ord){
    if(t[i] < T){
      double take = min(a[i] , Sn / (T - t[i]));
      Sn -= take * (T - t[i]);
      ret += take;
    }
  }
  for(int i : ord){
    if(t[i] == T)ret += a[i];
  }
  printf("%lf\n" , ret);
}
