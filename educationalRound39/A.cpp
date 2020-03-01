#include <bits/stdc++.h>
using namespace std;

int N;
int a[105];

int main(){
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cin >> N;
  int pos = 0 , neg = 0;
  for(int i = 1; i <= N; ++i){
    cin >> a[i];
    if(a[i] >= 0)pos += a[i];
    else neg += a[i];
  }
  cout << pos - neg << endl;
}
