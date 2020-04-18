#include <bits/stdc++.h>
#define DEBUG(x) std::cerr << #x << '=' << x << std::endl
using namespace std;
typedef long long ll;
typedef pair<int , int> ii;

vector<int> find_subset(int L , int R , vector<int> w){
  vector<int> ret;
  int N = w.size();
  set<ii> canselect;
  for(int i = 0; i < N; ++i){
    if(w[i] < L){
      canselect.insert(make_pair(w[i] , i));
    }
    if(w[i] >= L && w[i] <= R){
      ret.push_back(i);
      return ret;
    }
  }
  ll sum = 0;
  set<ii> select;
  while(!canselect.empty()){
    if(sum >= L && sum <= R)break;
    auto it = *canselect.begin();
    if(it.first + sum > R){
      auto x = *canselect.rbegin();
      auto y = *select.begin();
      sum -= y.first;
      sum += x.first;
      select.erase(y);
      select.insert(x);
      canselect.erase(x);
    }
    else{ // sum < L
      sum += it.first;
      select.insert(it);
      canselect.erase(it);
    }
  }
  if(sum >= L && sum <= R){
    for(auto& e : select){
      ret.push_back(e.second);
    }
    return ret;
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
