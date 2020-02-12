#include <bits/stdc++.h>
using namespace std;

const int maxn = 1e2 + 10;
int N , a[maxn] , b[maxn] , W;

int main(){
  cin >> N >> W;
  vector<int> id;
  for(int i = 1; i <= N; ++i)cin >> a[i] , id.push_back(i);
  sort(id.begin() , id.end() , [&](int x , int y){
    return a[x] > a[y];
  });
  for(int i = 0; i < N; ++i){
    int j = id[i];
    int mv = ceil((double)a[j] / 2);
    b[j] = mv;
    W -= mv;
    if(W < 0){
      cout << -1 << endl;
      return 0;
    }
  }
  for(int i = 0; i < N && W; ++i){
    int j = id[i];
    if(W >= a[j] - b[j]){
      W -= a[j] - b[j];
      b[j] = a[j];
    }
    else{
      b[j] += W;
      W = 0;
    }
  }
  for(int i = 1; i <= N; ++i){
    cout << b[i] << " ";
  }
  cout << endl;
}
