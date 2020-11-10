#include <iostream>
#include <algorithm>
#include <vector>
#include <set>
using namespace std;
/*
--- very nice sweeping problem
first , if 2 time intervals in A intersect then they must intersect in B
So we have O(N ^ 2) solution
then , we sweep on the timestamps on A , and check if the corresponding intervals in B
intersect, this can be done by using multiset
*/
const int maxn = 1e5 + 10;
int N;
int sa[maxn] , sb[maxn] , ea[maxn] , eb[maxn];
struct event{
  int t , s , e , isin;
  event(){}
  event(int t_ , int s_ , int e_ , int isin_) : t(t_) , s(s_) , e(e_) , isin(isin_){}
  bool operator < (const event& r) const { // order by time of a , if tx = ty , delete first then add
    if(t == r.t)return isin < r.isin;
    return t < r.t;
  }
};

bool solve(){
  vector<event> events;
  multiset<int> starts , ends;
  for(int i = 1; i <= N; ++i){
    events.emplace_back(sa[i] , sb[i] , eb[i] , 1);
    events.emplace_back(ea[i] + 1 , sb[i] , eb[i] , 0);
  }
  sort(events.begin() , events.end());
  for(int i = 0; i < 2 * N; ++i){
    if(events[i].isin){
      if(starts.size()){
        int maxS = *starts.rbegin();
        int minE = *ends.begin();
        if(max(maxS , events[i].s) > min(minE , events[i].e)) // do not intersect
          return false;
      }
      starts.insert(events[i].s);
      ends.insert(events[i].e);
    }
    else{
      starts.erase(starts.find(events[i].s));
      ends.erase(ends.find(events[i].e));
    }
  }
  return true;
}

int main(){
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cin >> N;
  for(int i = 1; i <= N; ++i){
    cin >> sa[i] >> ea[i] >> sb[i] >> eb[i];
  }
  bool ret = 1;
  ret &= solve();
  for(int i = 1; i <= N; ++i){
    swap(sa[i] , sb[i]);
    swap(ea[i] , eb[i]);
  }
  ret &= solve();
  if(ret) cout << "YES" << endl;
  else cout << "NO" << endl;
}
