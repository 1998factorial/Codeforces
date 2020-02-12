#include <bits/stdc++.h>
using namespace std;
typedef pair<string , int> ii;
/*
  sort by a[i]
  set h[i] = i - a[i] to make sure he is at least taller than i - a[i] ppl
  for each h[j] >= h[i] , j < i , += 1
*/
const int maxn = 3e3 + 10;
int N;
ii person[maxn];
int h[maxn];

int main(){
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cin >> N;
  for(int i = 1; i <= N; ++i){
    cin >> person[i].first >> person[i].second;
  }
  sort(person + 1 , person + 1 + N , [&](ii a , ii b){
    return a.second < b.second;
  });
  for(int i = 1; i <= N; ++i){
    if(person[i].second >= i){
      cout << -1 << endl;
      return 0;
    }
    h[i] = i - person[i].second;
    for(int j = 1; j < i; ++j){
      if(h[j] >= h[i])++h[j];
    }
  }
  for(int i = 1; i <= N; ++i){
    cout << person[i].first << " " << h[i] << endl;
  }
  return 0;
}
