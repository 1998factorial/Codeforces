#include <bits/stdc++.h>
using namespace std;

int main(){
  srand(time(NULL));
  int N = 2e5;
  printf("%d\n" , N);
  for(int i = 1; i <= N; ++i){
    //int a = rand() % 1000000000 + 1;
    printf("%d ", i + 5);
  }
  puts("\n");
}
