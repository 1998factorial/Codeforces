
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <vector>
using namespace std;
typedef long long ll;
typedef pair<int , int > ii;

const int maxn = 3e5 + 10;
int p[maxn] , q[maxn];
int T;
int M , N;

int main(){
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cin >> T;
  for(int t = 1; t <= T; ++t){
    cin >> N;
    for(int i = 1; i <= N; ++i)cin >> p[i];
    cin >> M;
    for(int i = 1; i <= M; ++i)cin >> q[i];
    int a = 0 , b = 0 , c = 0 , d = 0;
    for(int i = 1; i <= N; ++i){
      if(p[i] % 2 == 0)++a;
      else ++b;
    }
    for(int i = 1; i <= M; ++i){
      if(q[i] % 2 == 0)++c;
      else ++d;
    }
    cout << (ll)a * c + (ll)b * d << endl;
  }
  return 0;
}
