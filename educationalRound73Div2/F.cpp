#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>
using namespace std;

const int maxn = 5e5 + 10;
int N;

struct point{
  int x , y , c;
  bool operator<(const point& other) const {
    if(other.x == x)return y < other.y;
    return x < other.x;
  }
}P[maxn];

int main(){
  cin >> N;
  for(int i = 1; i <= N; ++i){
    cin >> P[i].x >> P[i].y >> P[i].c;
  }
  sort(P + 1 , P + 1 + N);
  vector<int> X , Y;
  for(int i = 1; i <= N; ++i){
    X.push_back(P[i].x);
    Y.push_back(P[i].y);
  }
  sort(X.begin() , X.end());
  return 0;
}
