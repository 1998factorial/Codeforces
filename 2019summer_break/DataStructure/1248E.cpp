#include <iostream>
#include <algorithm>
#include <set>
#include <queue>
#include <vector>
#include <deque>
using namespace std;
typedef long long ll;
typedef pair<int , int> ii;

/*
  simulation
*/

priority_queue<ii , vector<ii> , greater<ii>> q;
deque<int> wait_list;
set<int> want_list;

const int maxn = 1e5 + 10;
int N , P;
ll ans[maxn];

int main(){
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cin >> N >> P;
  for(int i = 1; i <= N; ++i){
    int t; cin >> t;
    q.push(make_pair(t , i));
  }
  ll cur_time = 0;
  while(!q.empty() || !wait_list.empty() || !want_list.empty()){
    if(wait_list.empty() && want_list.empty())cur_time = q.top().first; // if no one in queue or want to go , reset current time
    cur_time += P; // we need at least extra P for the next person to complete
    while(!q.empty() && q.top().first <= cur_time){ // add all "avaiable" people into either wait list or want list
      if(wait_list.empty() || q.top().second < wait_list.back()) // if wait list is empty or this person's
        wait_list.push_back(q.top().second);
      else
        want_list.insert(q.top().second);
      q.pop();
    }
    ans[wait_list.front()] = cur_time;
    wait_list.pop_front();
    if(!want_list.empty() && wait_list.empty()){
      wait_list.push_back(*want_list.begin());
      want_list.erase(*want_list.begin());
    }
  }
  for(int i = 1; i <= N; ++i){
    cout << ans[i] << " ";
  }
}
