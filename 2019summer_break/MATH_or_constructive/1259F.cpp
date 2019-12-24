#include <iostream>
#include <algorithm>
#include <map>
#include <vector>
using namespace std;
typedef long long ll;
const int maxn = 4e5 + 10;
int N;
int a[maxn];
int atleast[maxn];
vector<int> val_by_cnt[maxn];

int main(){
  map<int , int> cnt;
  cin >> N; for(int i = 1; i <= N; ++i)cin >> a[i] , ++cnt[a[i]];
  for(auto& it : cnt){
    val_by_cnt[it.second].push_back(it.first);
  }
  atleast[N] = val_by_cnt[N].size();
  for(int i = N - 1; i >= 0; --i){
    atleast[i] = atleast[i + 1] + val_by_cnt[i].size();
  }
  int best = 0 , ba = -1 , bb = -1 , tot = 0;
  for(int a = 1; a <= N; ++a){
    tot += atleast[a];
    int b = tot / a;
    if(a <= b && a * b > best){
      ba = a; bb = b; best = a * b;
    }
  }
  cout << best << endl;
  cout << ba << " " << bb << endl;
  vector<vector<int>> ret(ba , vector<int>(bb));
  int x = 0 , y = 0;
  for(int i = N; i >= 1; --i){
    for(int val : val_by_cnt[i]){
      for(int j = 0; j < min(i , ba); ++j){
        if(ret[x][y] != 0)
          x = (x + 1) % ba;
        if(ret[x][y] == 0)
          ret[x][y] = val;
        x = (x + 1) % ba;
        y = (y + 1) % bb;
      }
    }
  }
  for(int i = 0; i < ba; ++i){
    for(int j = 0; j < bb; ++j){
      cout << ret[i][j] << " ";
    }
    cout << endl;
  }
}
