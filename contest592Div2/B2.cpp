#include <iostream>
#include <cstring>
#include <cstdio>
#include <algorithm>
using namespace std;

int N;
string a;

int main(){
  int T;
  cin >> T;
  for(int t = 1; t <= T; ++t){
    cin >> N;
    cin >> a;
    int ret = 0;
    int cnt = 0;
    for(int i = 0; i < N; ++i){
      if(a[i] == '1')++cnt;
    }
    if(cnt == 0){
      cout << N << endl;
    }
    else if(cnt == 1){
      int pos = 0;
      for(int i = 0; i < N; ++i)if(a[i] == '1')pos = i;
      cout << 2 * max(pos + 1 , N - pos) << endl;
    }
    else{
      for(int i = 0 ; i < N; ++i){
        if(a[i] == '0')continue;
        ret = max(ret , 2 * (N - i));
        ret = max(ret , 2 * (i + 1));
        for(int j = i + 1; j < N; ++j){
          if(a[j] == '1'){
            ret = max(ret , 2 * (j - i + 1));
          }
        }
      }
      cout << ret << endl;
    }
  }
  return 0;
}
