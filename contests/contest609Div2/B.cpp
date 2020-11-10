#include <iostream>
#include <unordered_map>
#include <algorithm>
#include <vector>
using namespace std;

int N , M;
int a[2005] , b[2005];
vector<int> freq1[2005] , freq2[2005];

int main(){
  cin >> N >> M;
  unordered_map<int , int> cnt1 , cnt2 , inv1 , inv2;
  for(int i = 1; i <= N; ++i)cin >> a[i] , cnt1[a[i]]++;
  for(int i = 1; i <= N; ++i)cin >> b[i] , cnt2[b[i]]++;
  for(auto& it : cnt1){
    freq1[it.second].push_back(it.first);
  }
  for(auto& it : cnt2){
    freq2[it.second].push_back(it.first);
  }
  for(int i = 0; i <= N; ++i){
    if(freq1[i].size()){
      sort(freq1[i].begin() , freq1[i].end() , [&](int x , int y){
        return x < y;
      });
    }
  }

  for(int i = 0; i <= N; ++i){
    if(freq2[i].size()){
      sort(freq2[i].begin() , freq2[i].end() , [&](int x , int y){
        return x < y;
      });
    }
  }
  int ret = 1e9;
  for(int i = 0; i <= N; ++i){
    if(freq1[i].size()){
      cout << i << " : ";
      for(int j : freq1[i])cout << j << " ";
      cout << endl;
      cout << i << " : ";
      for(int j : freq2[i])cout << j << " ";
      cout << endl;

      ret = ((freq2[i][0] - freq1[i][0]) % M + M) % M;
      break;
    }
  }
  cout << ret << endl;
}
