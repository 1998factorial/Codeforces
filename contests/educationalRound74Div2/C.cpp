#include <iostream>
#include <vector>
using namespace std;

int main(){
  int Q;
  cin >> Q;
  for(int q = 1; q <= Q; ++q){
    int h , n;
    cin >> h >> n;
    vector<int> p;
    for(int i = 1; i <= n; ++i){
      int x;
      cin >> x;
      p.push_back(x);
    }
    p.push_back(0);
    int cnt = 0;
    int i = 0;
    while(i + 2 <= n){
      if(h == p[i + 1] + 1){
        if(p[i + 1] > p[i + 2] + 1)++cnt , h = p[i + 2] + 1;
        else h = p[i + 2];
        i += 2;
      }
      else ++i , h = p[i];
    }
    cout << cnt << endl;
  }
  return 0;
}
