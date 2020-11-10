#include <iostream>
#include <cstring>
#include <cstdio>
using namespace std;

int N , K;
string s;
int a[1000][2];

// N <= 2e5 , K <= 1e9

int main(){
  cin >> N >> K;
  cin >> s;
  for(int i = 0; i < N; ++i){
    a[i][0] = (s[i] == 'B') ? 1 : -1;
  }
  for(int i = 0; i <= K; ++i){
    for(int j = 0; j < N; ++j){
      a[j][(i + 1) % 2] = (a[(j - 1 + N) % N][i % 2] + a[j][i % 2] + a[(j + 1) % N][i % 2] < 0) ? -1 : 1;
    }
  }
  for(int j = 0; j < N; ++j){
    if(a[j][K % 2] == 1)cout << "B";
    else cout << "W";
  }
  cout << endl;
  return 0;
}
