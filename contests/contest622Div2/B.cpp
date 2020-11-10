#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int N , x , y;

/*
  min :
  1 .... x + y
  1 .... x + y , -> a + b = x + y + 1

  max :
  1 .... x + y - 1
  1 .... x + y - 1 -> a + b = x + y
*/

int main(){
  int t;
  cin >> t;
  while(t--){
    cin >> N >> x >> y;
    if(x + y <= N)cout << 1 << " ";
    else{
      cout << min(N , x + y - N + 1) << " ";
    }
    cout << min(N , x + y - 1) << endl;
  }
}
