#pragma GCC optimize(3)
#pragma GCC optimize(2)
#include <bits/stdc++.h>
#define DEBUG(x) std::cerr << #x << '=' << x << std::endl
using namespace std;
typedef long long ll;
typedef pair<int , int> ii;

const int maxn = 4e4 + 10;
int N , M , K;
int a[maxn] , b[maxn];

unordered_map<int , ll> fa , fb;

int main(){
  scanf("%d %d %d" , &N , &M , &K);
  for(int i = 1; i <= N; ++i){
    scanf("%d" , &a[i]);
  }
  for(int i = 1; i <= M; ++i){
    scanf("%d" , &b[i]);
  }
  vector<int> t;
  for(int i = 1; i <= N; ++i){
    if(a[i] == 1)t.push_back(i);
    else {
      if(!t.empty()){
        fa[t.size()]++;
        t.clear();
      }
    }
  }
  if(!t.empty()){
    fa[t.size()]++;
    t.clear();
  }
  for(int i = 1; i <= M; ++i){
    if(b[i] == 1)t.push_back(i);
    else {
      if(!t.empty()){
        fb[t.size()]++;
        t.clear();
      }
    }
  }
  if(!t.empty()){
    fb[t.size()]++;
    t.clear();
  }
  ll ans = 0;
  for(int i = 1; i * i <= K; ++i){
    if(K % i == 0){
      for(auto& A : fa){
        for(auto& B : fb){
          int x = i , y = K / i;
          int X = A.first , Y = B.first;
          if(X >= x && Y >= y){
            ans += (ll)(X - x + 1) * (Y - y + 1) * A.second * B.second;
          }
          if(x == y)continue;
          if(X >= y && Y >= x){
            ans += (ll)(Y - x + 1) * (X - y + 1) * A.second * B.second;
          }
        }
      }
    }
  }
  printf("%lld\n" , ans);
}
