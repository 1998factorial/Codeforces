#pragma GCC optimize(3)
#pragma GCC optimize(2)
#include <bits/stdc++.h>
#define DEBUG(x) std::cerr << #x << '=' << x << std::endl
using namespace std;
typedef long long ll;
typedef pair<int , int> ii;


int main(){
  int T = 5;
  srand(time(NULL));
  cout << T << endl;
  for(int t = 1; t <= T; ++t){
    int N = 6 , K = 2;
    cout << N << " " << K << endl;
    vector<string> r;
    for(int i = 1; i <= N; ++i){
      int len = rand() % 5 + 1;
      string t = "";
      for(int j = 1; j <= len; ++j){
        char a = 'A' + rand() % 4;
        t += a;
      }
      r.push_back(t);
    }
    sort(r.begin() , r.end());
    for(string t : r){
      cout << t << endl;
    }
  }
}
