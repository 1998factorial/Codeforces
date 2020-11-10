#pragma GCC optimize(3)
#pragma GCC optimize(2)
#include <bits/stdc++.h>
#define DEBUG(x) std::cerr << #x << '=' << x << std::endl
using namespace std;
typedef long long ll;
typedef pair<int , int> ii;


int main(){
  int T; scanf("%d" , &T);
  while(T--){
    ll n , g , b;
    scanf("%lld %lld %lld", &n , &g , &b);
    ll goal = ceil((double)n / 2.0);
    if(goal <= g)printf("%lld\n" , n);
    else{
      ll rem = (goal % g == 0) ? -b : goal % g;
      printf("%lld\n" , max(n , (goal / g) * (g + b) + rem));
    }
  }
}
