#pragma GCC optimize(3)
#pragma GCC optimize(2)
#include <bits/stdc++.h>
#define DEBUG(x) std::cerr << #x << '=' << x << std::endl
using namespace std;
typedef long long ll;
typedef pair<int , int> ii;

int main(){
  int N = 5;
  srand(time(NULL));
  printf("%d\n" , N);
  for(int i = 1; i <= N; ++i){
    int x = (rand() % 200000000);
    if(rand() % 2)x *= -1;
    int t = rand() % 2000000;
    printf("%d %d\n" , x , t);
  }
  printf("%d\n" , rand() % 1000);
}
