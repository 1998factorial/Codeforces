#pragma GCC optimize(3)
#pragma GCC optimize(2)
#include <bits/stdc++.h>
#define DEBUG(x) std::cerr << #x << '=' << x << std::endl
using namespace std;
typedef long long ll;
typedef pair<int , int> ii;
const int maxn = 4e5 + 10;
int a[maxn];
int N;

int solve(int k){
  // count the number of pairwise sum x,
  // such that (1 << k) <= x <= (1 << (k + 1)) - 1 or
  // (1 << (k + 1)) + (1 << k) <= x <= (1 << (k + 2)) - 2
  ll cnt = 0;
  vector<int> b;
  for(int i = 1; i <= N; ++i){
    b.push_back(a[i] % (1 << (k + 1)));
  }
  sort(b.begin() , b.end());
  //for(int x : b) cout << x << " ";
  //cout << endl;
  /*printf("find pair sum in [%d %d] or [%d %d]\n" ,
    (1 << k) , (1 << (k + 1)) - 1 ,
    (1 << k) + (1 << (k + 1)) ,
    (1 << (k + 2)) - 2
  );*/
  for(int x : b){
    auto it1 = lower_bound(b.begin() , b.end() , (1 << k) - x);
    auto it2 = upper_bound(b.begin() , b.end() , (1 << (k + 1)) - 1 - x);
    cnt += it2 - it1;
    if((1 << k) - x <= x && x <= (1 << (k + 1)) - 1 - x)--cnt;
    //printf("#x in [%d %d] = %d\n" , (1 << k) - x , (1 << (k + 1)) - 1 - x , it2 - it1);
    it1 = lower_bound(b.begin() , b.end() , (1 << k) + (1 << (k + 1)) - x);
    it2 = upper_bound(b.begin() , b.end() , (1 << (k + 2)) - 2 - x);
    cnt += it2 - it1;
    if((1 << k) + (1 << (k + 1)) - x <= x && x <= (1 << (k + 2)) - 2 - x)--cnt;
    //printf("#x in [%d %d] = %d\n" , (1 << k) + (1 << (k + 1)) - x , (1 << (k + 2)) - 2 - x , it2 - it1);
  }
  cnt /= 2;
  //cout << cnt << endl;
  return cnt % 2 == 1;
}

int main(){
  scanf("%d"  ,&N);
  for(int i = 1; i <= N; ++i){
    scanf("%d" , &a[i]);
  }
  int ans = 0;
  for(int i = 0; i < 25; ++i){
    if(solve(i)){ // solve for ith bit
      ans |= (1 << i);
    }
  }
  printf("%d\n" , ans);
}
