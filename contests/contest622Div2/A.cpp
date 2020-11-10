#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

bool vis[1 << 3];
int a[3];

int main(){
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  int t; cin >> t;
  while(t--){
    cin >> a[0] >> a[1] >> a[2];
    int ret = 0;
    for(int i = 0; i < 3; ++i)if(a[i])++ret , --a[i];
    sort(a , a + 3);
    if(a[2] && a[1])++ret , --a[2] , --a[1];
    if(a[2] && a[0])++ret , --a[2] , --a[0];
    if(a[1] && a[0])++ret , --a[1] , --a[0];
    if(a[2] && a[1] && a[0])++ret;
    cout << ret << endl;
  }
}
