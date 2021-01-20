#pragma GCC optimize(3)
#pragma GCC optimize(2)
#include <bits/stdc++.h>
#define DEBUG(x) std::cerr << #x << '=' << x << std::endl
using namespace std;
typedef long long ll;
typedef pair<int , int> ii;

double MAX[1 << 10][7][7];
double MIN[1 << 10][7][7];
string s;
int a , b;
double inf = 1234567890;

double getMax(int mask , int x, int y){
  if(!mask)return 0;
  if(MAX[mask][x][y] > 0){
    return MAX[mask][x][y];
  }
  double ret = 0;
  bool found = 0;
  for(int subset = mask; subset; subset = (subset - 1) & mask){
    int sum = 0;
    for(int i = 1; i <= 9; ++i)if((1 << i) & subset)sum += i;
    if(sum != x + y)continue;
    found = 1;
    double r = 0;
    for(int i = 1; i <= 6; ++i){
      for(int j = 1; j <= 6; ++j){
        r += getMax(mask ^ subset , i , j);
      }
    }
    r /= 36.0;
    if(r > ret)ret = r;
  }
  if(found)
    MAX[mask][x][y] = ret;
  else { // no valid state
    vector<int> t;
    for(int i = 1; i <= 9; ++i)if((1 << i) & mask)t.push_back(i);
    double val = 0;
    for(int i : t)val = 10.0 * val + i;
    MAX[mask][x][y] = val;
  }
  return MAX[mask][x][y];
}


void solve_max(){ // solve for minimal score
  int mask = 0;
  for(int i = 0; i < s.size(); ++i){
    mask |= (1 << (s[i] - '0'));
  }
  double best_score = -1;
  int best_choice = 0;
  for(int subset = mask; subset; subset = (subset - 1) & mask){
    int sum = 0;
    for(int i = 1; i <= 9; ++i){
      if((1 << i) & subset)sum += i; // get all digit sum in this choice
    }
    if(sum == a + b){
      double r = 0;
      for(int x = 1; x <= 6; ++x){
        for(int y = 1; y <= 6; ++y){
          r += getMax(mask ^ subset , x , y);
        }
      }
      r /= 36.0;
      if(r > best_score){
        best_score = r;
        best_choice = subset;
      }
    }
  }
  if(best_choice){
    vector<int> t;
    for(int i = 1; i <= 9; ++i){
      if((1 << i) & best_choice)t.push_back(i);
    }
    for(int i : t)cout << i;
    cout << " ";
    //cout << best_score << endl;
    printf("%.5lf\n" , best_score);
  }
  else{
    cout << -1 << " "; // can not choose any digits
    vector<int> t;
    for(int i = 1; i <= 9; ++i){
      if((1 << i) & mask)t.push_back(i);
    }
    double val = 0;
    for(int i : t)val = 10.0 * val + i;
    printf("%.5lf\n" , val);
  }
}

double getMin(int mask , int x, int y){
  if(!mask)return 0;
  if(MIN[mask][x][y] > 0){
    return MIN[mask][x][y];
  }
  double ret = inf;
  bool found = 0;
  for(int subset = mask; subset; subset = (subset - 1) & mask){
    int sum = 0;
    for(int i = 1; i <= 9; ++i)if((1 << i) & subset)sum += i;
    if(sum != x + y)continue;
    found = 1;
    double r = 0;
    for(int i = 1; i <= 6; ++i){
      for(int j = 1; j <= 6; ++j){
        r += getMin(mask ^ subset , i , j);
      }
    }
    r /= 36.0;
    if(r < ret)ret = r;
  }
  if(found)
    MIN[mask][x][y] = ret;
  else { // no valid state
    vector<int> t;
    for(int i = 1; i <= 9; ++i)if((1 << i) & mask)t.push_back(i);
    double val = 0;
    for(int i : t)val = 10.0 * val + i;
    MIN[mask][x][y] = val;
  }
  return MIN[mask][x][y];
}

void solve_min(){ // solve for minimal score
  int mask = 0;
  for(int i = 0; i < s.size(); ++i){
    mask |= (1 << (s[i] - '0'));
  }
  double best_score = inf;
  int best_choice = 0;
  for(int subset = mask; subset; subset = (subset - 1) & mask){
    int sum = 0;
    for(int i = 1; i <= 9; ++i){
      if((1 << i) & subset)sum += i; // get all digit sum in this choice
    }
    if(sum == a + b){
      double r = 0;
      for(int x = 1; x <= 6; ++x){
        for(int y = 1; y <= 6; ++y){
          r += getMin(mask ^ subset , x , y);
        }
      }
      r /= 36.0;
      if(r < best_score){
        best_score = r;
        best_choice = subset;
      }
    }
  }
  if(best_choice){
    vector<int> t;
    for(int i = 1; i <= 9; ++i){
      if((1 << i) & best_choice)t.push_back(i);
    }
    for(int i : t)cout << i;
    cout << " ";
    printf("%.5lf\n" , best_score);
  }
  else{
    cout << -1 << " "; // can not choose any digits
    vector<int> t;
    for(int i = 1; i <= 9; ++i){
      if((1 << i) & mask)t.push_back(i);
    }
    double val = 0;
    for(int i : t)val = 10.0 * val + i;
    printf("%.5lf\n" , val);
  }
}

int main(){
  //ios::sync_with_stdio(false);
  //cin.tie(nullptr);
  memset(MAX , 0 , sizeof(MAX));
  memset(MIN , 0 , sizeof(MIN));
  cin >> s >> a >> b;
  solve_min();
  solve_max();
}
