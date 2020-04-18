#include <bits/stdc++.h>
#define DEBUG(x) std::cerr << #x << '=' << x << std::endl
using namespace std;
typedef long long ll;
typedef pair<int , int> ii;

vector<int> find_subset(int L , int R , vector<int> w){
  vector<int> ret;
  set<ii> canselect , select;
  for(int i = 0; i < w.size(); ++i){
    if(w[i] >= L && w[i] <= R){
      ret.push_back(i);
      return ret;
    }
    if(w[i] < L){
      canselect.insert(make_pair(w[i] , i));
    }
  }
  ll sum = 0;
  while(!canselect.empty()){
    if(sum >= L && sum <= R)break;
    ii it = *canselect.begin();
    if(sum + it.first <= R){
      sum += it.first;
      select.insert(it);
      canselect.erase(it);
    }
    else { // increment + l <= r
      ii x = *canselect.rbegin();
      ii y = *select.begin();
      sum -= y.first;
      sum += x.first;
      select.erase(y);
      select.insert(x);
      canselect.erase(x);
    }
  }
  if(sum >= L && sum <= R){
    for(auto& e : select)ret.push_back(e.second);
  }
  return ret;
}

/*int main(){
  vector<int> w;
  int N , L , R;
  cin >> N >> L >> R;
  for(int i = 1; i <= N; ++i){
    int x; cin >> x;
    w.push_back(x);
  }
  vector<int> ret = find_subset(L , R , w);
  for(int i : ret){
    cout << i << " ";
  }
  cout << endl;
}*/
