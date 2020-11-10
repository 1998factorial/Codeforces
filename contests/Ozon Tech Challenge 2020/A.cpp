#pragma GCC optimize(3)
#pragma GCC optimize(2)
#include <bits/stdc++.h>
#define DEBUG(x) std::cerr << #x << '=' << x << std::endl
using namespace std;
typedef long long ll;
typedef pair<int , int> ii;

int a[1005] , b[1005];
bool vis[2005];

int main(){
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  int t; cin >> t;
  while(t--){
    int N;
    cin >> N;
    unordered_map<int , int> ca , cb;
    for(int i = 1; i <= N; ++i)cin >> a[i] , ca[a[i]]++;
    for(int i = 1; i <= N; ++i)cin >> b[i] , cb[b[i]]++;
    vector<int> ret;
    memset(vis , 0 , sizeof(vis));
    sort(a + 1 , a + 1 + N);
    sort(b + 1 , b + 1 + N);
    for(int i = 1; i <= N; ++i){
      for(int val = 2; val <= 2000; ++val){
        if(vis[val])continue;
        if(cb[val - a[i]]){
          ret.push_back(val - a[i]);
          cb[val - a[i]]--;
          vis[val] = 1;
        }
      }
    }
    for(int i = 1;  i<= N; ++i)cout << a[i] << " ";
    cout << endl;
    for(int i : ret)cout << i << " ";
    cout << endl;
  }
}
