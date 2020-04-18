#include <bits/stdc++.h>
using namespace std;

const int maxn = 1e9;

int main(){
  int N = 2e5;
  printf("%d\n" , N);
  srand(time(NULL));
  for(int i = 1; i <= N; ++i){
    int s = rand() % maxn + 1 , t = rand() % maxn + 1;
    printf("%d %d\n" , s , t);
  }
}
