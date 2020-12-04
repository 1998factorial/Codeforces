#pragma GCC optimize(3)
#pragma GCC optimize(2)
#include <bits/stdc++.h>
#define DEBUG(x) std::cerr << #x << '=' << x << std::endl
using namespace std;
typedef long long ll;
typedef pair<int , int> ii;

int N , T;
int U;
const int lim = 1e4;
vector<pair<int , string>> data;
vector<string> ret;

void solve(){
    cin >> U;
    ret.clear();
    for(int i = 1; i <= lim; ++i){
        int x; cin >> x;
        string y; cin >> y;
        ret.push_back(y);
    }
    sort(ret.begin() , ret.end());
    unordered_map<string , int> cnt;
    int len[100];
    len[1] = len[2] = 0;
    for(string& e : ret){
        ++cnt[e];
        ++len[(int)e.size()];
    }
    for(int i = 1; i <= U; ++i){
        printf("len[%d] = %d\n" , i , len[i]);
    }
}

int main(){
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cin >> T;
  for(int t = 1; t <= T; ++t){
    cout << "Case #" << t << ": ";
    solve();
  }
}
