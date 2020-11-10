#include <iostream>
#include <set>
using namespace std;

const int maxn = 1e5 + 10;
int N , Q;

int lava[3][maxn];
int good[maxn];
set<int> bads;

bool badsquare(int i){
  if(lava[1][i] && lava[2][i])return 1;
  if(lava[1][i + 1] && lava[2][i + 1])return 1;
  if(lava[1][i] && lava[2][i + 1])return 1;
  if(lava[2][i] && lava[1][i + 1])return 1;
  return 0;
}

int main(){
  cin >> N >> Q;
  for(int i = 1; i <= Q; ++i){
    int r , c; cin >> r >> c;
    lava[r][c] = 1 - lava[r][c];
    if(badsquare(c)){
      bads.insert(c);
    }
    else{
      bads.erase(c);
    }
    if(c - 1 >= 1){
      if(badsquare(c - 1)){
        bads.insert(c - 1);
      }
      else{
        bads.erase(c - 1);
      }
    }
    if(bads.empty())cout << "Yes" << endl;
    else cout << "No" << endl;
  }
}
