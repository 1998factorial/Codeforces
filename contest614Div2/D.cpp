#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
using namespace std;
typedef long long ll;
typedef pair<ll , ll> ii;

ll x_0 , y_0 , ax , ay , bx , by , ys , xs , t;
vector<ii> points;
int n;

ll dis(ll x1 , ll x2 , ll y1 , ll y2){
  return abs(x1 - x2) + abs(y1 - y2);
}

int solve(int pos){ // start with points[pos]
  ll time = t;
  int ret = 0;
  time -= dis(xs , points[pos].first , ys , points[pos].second);
  if(time >= 0)++ret;
  for(int i = pos - 1; i >= 0 && time > 0; --i){
    time -= dis(points[i + 1].first , points[i].first , points[i + 1].second , points[i].second);
    if(time >= 0)++ret;
  }
  if(time <= 0)return ret;
  if(pos + 1 < n)time -= dis(points[0].first , points[pos + 1].first , points[0].second , points[pos + 1].second);
  if(time >= 0 && pos + 1 < n)++ret;
  for(int i = pos + 2; i < n && time > 0; ++i){
    time -= dis(points[i - 1].first , points[i].first , points[i - 1].second , points[i].second);
    if(time >= 0)++ret;
  }
  return ret;
}

int main(){
  cin >> x_0 >> y_0 >> ax >> ay >> bx >> by;
  cin >> xs >> ys >> t;
  ll x = ax * x_0 + bx , y = ay * y_0 + by;
  points.emplace_back(x_0 , y_0);
  while(dis(x , x_0 , y , y_0) <= (1ll << 61)){
    points.emplace_back(x , y);
    x_0 = x;
    y_0 = y;
    if((int)log10(ax) + log10(x_0) > 18 || (int)log10(ay) + log10(y_0) > 18)break;
    x = ax * x_0 + bx , y = ay * y_0 + by;
    if(x - x_0 > (1ll << 61) - y + y_0)break;
    if(x - x_0 > (1ll << 61))break;
    if(y - y_0 > (1ll << 61))break;
  }
  n = points.size();
  int ret = 0;
  int bi = 0;
  for(int i = 0; i < n; ++i){
    int r = solve(i);
    if(r > ret){
      ret = r; bi = i;
    }
  }
  cout << ret << endl;
}
