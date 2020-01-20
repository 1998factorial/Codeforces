#include <iostream>
#include <cstring>
#include <string.h>
#include <queue>
#include <algorithm>
#include <vector>
using namespace std;


int S , D;
string inf;
bool vis[505][5005];
int pre[505][5005];

struct state{
  int remain , sum;
  state(){}
  state(int r , int s): remain(r) , sum(s) {}
};

int qpow(int x , int n){
  if(n <= 0)return 1;
  int ret = qpow(x , n / 2);
  ret = ret * ret % D;
  if(n % 2 == 1)ret = ret * x % D;
  return ret;
}

string solve(int remain , int sum){
  queue<state> q;
  pre[0][0] = -1;
  for(int i = 1; i <= 9; ++i){
    q.push(state(i % D , i));
    pre[i % D][i] = i;
  }
  while(!q.empty()){
    auto cur = q.front();
    q.pop();
    int s = cur.sum , r = cur.remain;
    if(s > S)continue;
    if(s == S && r == 0){
      string ret = "";
      while(pre[r][s] != -1){
        cout << r << " " << s << endl;
        ret += '0' + pre[r][s];
        int ns = s - pre[r][s];
        int nr = ((r - pre[r][s]) * qpow(10 , D - 2) % D + D) % D;
        s = ns , r = nr;
      }
      return ret;
    }
    if(!vis[r][s]){
      vis[r][s] = 1;
      for(int x = 0; x < 10; ++x){
        int ns = s + x , nr = (10 * r + x) % D;
        if(!vis[nr][ns]){
          pre[nr][ns] = x;
          q.push(state(nr , ns));
        }
      }
    }
  }
  return "-1";
}

int main(){
  cin >> D >> S;
  for(int i = 0; i < D; ++i){
    for(int j = 0; j <= S; ++j){
      pre[i][j] = -1;
    }
  }
  if(S == 0){
    if(D == 0)cout << "0" << endl;
    else cout << "-1" << endl;
  }
  else{
    cout << solve(D , S) << endl;
  }
}
