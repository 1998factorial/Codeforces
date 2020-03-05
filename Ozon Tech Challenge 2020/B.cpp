#pragma GCC optimize(3)
#pragma GCC optimize(2)
#include <bits/stdc++.h>
#define DEBUG(x) std::cerr << #x << '=' << x << std::endl
using namespace std;
typedef long long ll;
typedef pair<int , int> ii;

/*
  find the longest good string
*/

string s;
bool vis[1005];
vector<int> ret[1005];

int main(){
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cin >> s;
  int l = 0 , r = s.size() - 1;
  vector<int> L , R;
  while(l <= r){
    while(l <= r && s[l] == ')')++l;
    while(r >= l && s[r] == '(')--r;
    if(l < r){
      L.push_back(l);
      R.push_back(r);
      ++l; --r;
    }
  }
  if(L.size() == 0){
    cout << 0 << endl;
  }
  else{
    cout << 1 << endl;
    cout << 2 * L.size() << endl;
    for(int i : L)cout << i + 1 << " ";
    reverse(R.begin() , R.end());
    for(int i : R)cout << i + 1 << " ";
    cout << endl;
  }
}
