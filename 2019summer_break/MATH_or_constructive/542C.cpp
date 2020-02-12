#include <bits/stdc++.h>
using namespace std;

int N;
int F[205][505];

int main(){
  cin >> N;
  for(int i = 1; i <= N; ++i){
    cin >> F[i][1];
  }
  for(int j = 2; j <= 500; ++j){
    for(int i = 1; i <= N; ++i){
      F[i][j] = F[F[i][j - 1]][1];
    }
  }
  for(int i = 1; i <= 500; ++i){
    int ok = 1;
    for(int j = 1; j <= N; ++j){
      if(F[F[j][i]][i] != F[j][i])ok = 0;
    }
    if(ok){
      cout << i << endl;
      return 0;
    }
  }
}
