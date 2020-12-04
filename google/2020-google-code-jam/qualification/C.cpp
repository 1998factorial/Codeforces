#pragma GCC optimize(3)
#pragma GCC optimize(2)
#include <bits/stdc++.h>
#define DEBUG(x) std::cerr << #x << '=' << x << std::endl
using namespace std;
typedef long long ll;
typedef pair<int , int> ii;

int T , N;
char ret[1005];
struct event{
  int s , e , id;
  event(){}
  event(int a , int b , int c) : s(a) , e(b) , id(c) {}
  bool operator < (const event& rhs) const {
    if(s != rhs.s)return s < rhs.s;
    if(e != rhs.e)return e < rhs.e;
    return id < rhs.id;
  }
};
vector<event> events;

string solve(){
  cin >> N;
  events.clear();
  for(int i = 1; i <= N; ++i){
    int x , y; cin >> x >> y;
    events.emplace_back(x , y , i);
  }
  sort(events.begin() , events.end());
  int ce = -1 , je = -1;
  for(auto& e : events){
    if(e.s >= ce){
      ce = e.e;
      ret[e.id] = 'C';
    }
    else if(e.s >= je){
      je = e.e;
      ret[e.id] = 'J';
    }
    else{
      return "IMPOSSIBLE";
    }
  }
  string ans = "";
  for(int i = 1; i <= N; ++i)ans += ret[i];
  return ans;
}

int main(){
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cin >> T;
  for(int t = 1; t <= T; ++t){
    cout << "Case #" << t << ": " << solve() << endl;
  }
}
