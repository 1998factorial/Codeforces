#pragma GCC optimize(3)
#pragma GCC optimize(2)
#include <bits/stdc++.h>
#define DEBUG(x) std::cerr << #x << '=' << x << std::endl
using namespace std;
typedef long long ll;
typedef pair<int , int> ii;

int T , N;
int pos[256];
string P[256];
bool win[256];


void NO(){
  cout << "IMPOSSIBLE" << endl;
}

char check(char a){
  if(a == 'R')return 'P';
  if(a == 'S')return 'R';
  return 'S';
}

void answer(){
  cin >> N;
  for(int i = 1; i <= N; ++i)cin >> P[i];
  for(int i = 1; i <= N; ++i)pos[i] = win[i] = 0;
  int cnt = N;
  string ret = "";
  for(;cnt;){
    set<char> vis;
    char op;
    for(int i = 1; i <= N; ++i){
      if(!win[i]){
        vis.insert(P[i][pos[i]]);
      }
    }
    if(vis.size() == 3){
      NO();
      return;
    }
    if(vis.size() == 2){
      vector<char> ops;
      for(char x : vis)ops.push_back(x);
      if(check(ops[0]) == ops[1])op = ops[1];
      else op = ops[0];
    }
    if(vis.size() == 1){
      op = check(*vis.begin());
    }
    for(int i = 1; i <= N; ++i){
      if(!win[i]){
        if(op == check(P[i][pos[i]])){
          win[i] = 1; --cnt;
        }
        else{
          pos[i] = (pos[i] + 1) % P[i].size();
        }
      }
    }
    ret += op;
  }
  cout << ret << endl;
}

int main(){
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cin >> T;
  for(int t = 1; t <= T; ++t){
    cout << "Case #" << t << ": ";
    answer();
  }
}
