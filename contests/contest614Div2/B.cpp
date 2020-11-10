#include <iostream>
using namespace std;

int main(){
  int N;
  cin >> N;
  double ret = 0;
  for(int i = 1; i <= N; ++i){
    ret += 1.0 / (double)i;
  }
  printf("%lf\n" , ret);
}
