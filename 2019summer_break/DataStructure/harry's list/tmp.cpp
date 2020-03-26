#include <bits/stdc++.h>
using namespace std;

const int maxn = 2e5 + 10;
int a[maxn];
int N;

int main(){
  cin >> N;
  for(int i = 0; i < N; ++i){
    cin >> a[i];
  }
  if(N <= 1){
    cout << 0 << endl;
  }
  else{
    int i = 0;
    int best = 0;
    int mx = 0;
    for(int j = 1; j < N; ++j){
      if(a[j - 1] < a[j]){
        if(mx < j - i + 1){
          mx = j - i + 1;
          best = i;
        }
      }
      else{
        i = j;
      }
    }
    cout << best << endl;
  }
}
