#pragma GCC optimize(3)
#pragma GCC optimize(2)
#include <bits/stdc++.h>
#define DEBUG(x) std::cerr << #x << '=' << x << std::endl
using namespace std;
typedef long long ll;
typedef pair<int , int> ii;
int a[105];
int main(){
  int t; cin >> t;
  while(t--){
    int N;
    cin >> N;
    for(int i = 1; i <= N; ++i)cin >> a[i];
    sort(a + 1 , a + 1 + N);
    for(int i = N; i >= 1; --i)cout << a[i] << " ";
    cout << endl;
  }
}
