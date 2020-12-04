#pragma GCC optimize(3)
#pragma GCC optimize(2)
#include <bits/stdc++.h>
#define DEBUG(x) std::cerr << #x << '=' << x << std::endl
using namespace std;
typedef long long ll;
typedef pair<int , int> ii;

const int maxn = 10;
char a[maxn][maxn];
char t[maxn][maxn];
/*
  enumerate all subsets of diagonals going from top-left to bottom-right
  this gives 2 ^ (2 * N - 1) choices
  then check if we can complete the square with some diagonals going from top-right to
  bottom-left
  solution is O(2 ^ (2 * N - 1) * N * N)
  which suffices for N <= 8

  (I am too lazy to complete the brute force solution :p)
*/
struct diag{
  int x1 , y1 , x2 , y2;
  diag(){}
  diag(int a , int b , int c , int d): x1(a) , y1(b) , x2(c) , y2(d){}
};

vector<diag> D;
int N;

bool check(char val){
  for(int i = 1; i <= N; ++i){
    for(int j = 1; j <= N; ++j){
      if(t[i][j] != val)return 0;
    }
  }
  return 1;
}

void copy(){
  for(int i = 1; i <= N; ++i){
    for(int j = 1; j <= N; ++j){
      t[i][j] = a[i][j];
    }
  }
}

void flip(int i , int j){
  if(t[i][j] == '.')t[i][j] = '#';
  else if(t[i][j] == '#')t[i][j] = '.';
}

int solve(){
  D.clear();
  cin >> N;
  for(int i = 1; i <= N; ++i){
    for(int j = 1; j <= N; ++j){
      cin >> a[i][j];
    }
  }
  D.emplace_back(1 , 1 , N , N);
  for(int i = 1; i <= N - 1; ++i){
    D.emplace_back(1 + i , 1 , N , N - i);
    D.emplace_back(1 , 1 + i , N - i , N);
  }
  int ret = 4 * N - 2;
  for(int state = 0; state < (1 << (2 * N - 1)); ++state){
    copy();
    for(int i = 0; i < D.size(); ++i){
      if((1 << i) & state){
        for(int j = 1; j <= D[i].x2 - D[i].x1 + 1; ++j){
          flip(D[i].x1 + j - 1 , D[i].y1 + j - 1);
        }
      }
    }
    if(check('.')){
      ret = min(ret , (int)__builtin_popcount(state) + 2 * N - 1);
    }
    else if(check('#')){
      ret = min(ret , (int)__builtin_popcount(state));
    }
  }
  return ret;
}


int main(){
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  int t; cin >> t;
  for(int x = 1; x <= t; ++x){
    cout << "Case #" << x << ": " << solve() << endl;
  }
}
