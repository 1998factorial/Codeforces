#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int , int> ii;

const int maxn = 4e5 + 10;
const int inf = 1e9 + 10;
struct edge{
  int from , to , cost;
  edge(){}
  edge(int a , int b , int c) : from(a) , to(b) , cost(c) {}
  bool operator < (const edge& rhs) const {
    return cost < rhs.cost;
  }
};
int id[maxn];
ll sum[maxn];

int find(int x){
  return x == id[x] ? x : id[x] = find(id[x]);
}

bool unite(int x , int y){
  x = find(x);
  y = find(y);
  if(x == y)return 0;
  id[x] = y;
  return 1;
}

ll plan_roller_coaster(vector<int> s , vector<int> t){
  s.push_back(inf);
  t.push_back(1);
  int N = s.size();
  vector<int> tmp;
  for(int i : s)tmp.push_back(i);
  for(int i : t)tmp.push_back(i);
  sort(tmp.begin() , tmp.end());
  int cnt = 1;
  // discrete
  unordered_map<int , int> mp , imp;
  for(int i : tmp){
    if(!mp[i]){
      mp[i] = cnt;
      imp[cnt] = i;
      ++cnt;
    }
  }
  --cnt;
  ll ans = 0;
  // init
  for(int i = 1; i <= cnt; ++i)id[i] = i , sum[i] = 0;
  for(int i = 0; i < N; ++i){
    int S = s[i] , T = t[i];
    ++sum[mp[S]];
    --sum[mp[T]];
    unite(mp[S] , mp[T]);
  }
  for(int i = 1; i < cnt; ++i){
    sum[i] += sum[i - 1];
  }
  for(int i = 1; i < cnt; ++i){
    if(sum[i] != 0)unite(i + 1 , i);
    if(sum[i] > 0){
      ans += sum[i] * (imp[i + 1] - imp[i]);
    }
  }
  vector<edge> edges;
  for(int i = 1; i < cnt; ++i){
    if(find(i + 1) != find(i)){
      edges.emplace_back(i , i + 1 , imp[i + 1] - imp[i]);
    }
  }
  sort(edges.begin() , edges.end());
  for(auto& e : edges){
    int x = e.from , y = e.to;
    if(unite(x , y)){
      ans += e.cost;
    }
  }
  return ans;
}

/*int main(){
  int N;
  cin >> N;
  vector<int> s , t;
  for(int i = 1; i <= N; ++i){
    int x , y;
    cin >> x >> y;
    s.push_back(x);
    t.push_back(y);
  }
  ll ret = plan_roller_coaster(s , t);
  cout << ret << endl;
}
*/
