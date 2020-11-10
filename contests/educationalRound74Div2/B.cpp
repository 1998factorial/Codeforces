#include <iostream>
#include <algorithm>
#include <cstdio>
using namespace std;

const int maxn = 1e5 + 10;
int x[maxn];

// 2 pointers

int main(){
  int Q;
  cin >> Q;
  for(int q = 1; q <= Q; ++q){
    int N , r;
    scanf("%d %d" , &N , &r);
    for(int i = 1; i <= N; ++i){
      scanf("%d" , &x[i]);
    }
    sort(x + 1 , x + N + 1);
    int ret = 0;
    int i = N , j = 1;
    while(i >= j ){
      int k = i;
      ++ret;
      while(k >= j && x[i] == x[k])--k;
      i = k;
      while(i >= j && x[j] - ret * r <= 0)++j;
    }
    cout << ret << endl;
  }
  return 0;
}
