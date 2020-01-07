#include <iostream>
#include <cstring>
#include <algorithm>
using namespace std;

int N , K;

string a;

int main(){
  cin >> N >> K;
  cin >> a;
  string p = a;
  a = a.substr(0 , K);
  string t = a;
  int len = K;
  for(; len < N;)a += t , len += K;
  a = a.substr(0 , N);
  if(a < p){
    for(int i = K - 1; i >= 0; --i){
      if(a[i] == '9')a[i] = '0';
      else{
        a[i] += 1;
        break;
      }
    }
    for(int i = K; i < N; ++i)a[i] = a[i - K];
  }
  cout << N << endl;
  cout << a << endl;
}
