#include <iostream>
#include <algorithm>
#include <queue>
#include <set>
#include <vector>
using namespace std;
typedef long long ll;
typedef pair<ll , ll> ii;
const int maxn = 1e5 + 10;
priority_queue<ii , vector<ii> , greater<ii>> q;
deque<int> wait_list;
set<int> want_list;
ll ans[maxn];
int N , p;

int main(){
  cin >> N >> p;
  for(int i = 1; i <= N; ++i){
    ll t; cin >> t; q.push(make_pair(t , i));
  }
  ll cur = 0;
  for(int i = 1; i <= N; ++i){
    if(wait_list.empty() && want_list.empty())cur = q.top().first;
    cur += p;
    while(!q.empty() && q.top().first <= cur){
      if(wait_list.empty() || q.top().second < wait_list.back())
        wait_list.push_back(q.top().second);
      else
        want_list.insert(q.top().second);
      q.pop();
    }
    ans[wait_list.front()] = cur;
    wait_list.pop_front();
    if(wait_list.empty() && !want_list.empty()){
      wait_list.push_back(*want_list.begin());
      want_list.erase(want_list.begin());
    }
  }
  for(int i = 1; i <= N; ++i)cout << ans[i] << " ";
  cout << endl;
}
