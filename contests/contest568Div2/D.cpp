#include <iostream>
#include <algorithm>
#include <cstring>
#include <cstdio>
#include <vector>
using namespace std;
const int maxn = 2e5 + 10;
int n;
int a[maxn];
vector<int> mp;
/*
  a[1] <=  a[2] <= a[3] <= ... <= a[n]
  if we delete a[1] , check if a[2] .. a[n] is arithmetic seq
  if we delete a[2] , check if a[1] , a[3] , .. , a[n]
  else we have the c = a[2] - a[1] and we check the remaining a[i]
*/

bool deleteFirst(){
  int c = a[mp[2]] - a[mp[1]];
  for(int i = 2; i < n; ++i){
    if(a[mp[i]] - a[mp[i - 1]] != c)return false;
  }
  return true;
}

bool deleteSecond(){
  int c = a[mp[2]] - a[mp[0]];
  for(int i = 3; i < n; ++i){
    if(a[mp[i]] - a[mp[i - 1]] != c)return false;
  }
  return true;
}

int check(){
  int c = a[mp[1]] - a[mp[0]];
  int ret = -1;
  int cnt = 1;
  int i = 2;
  int pre = a[mp[1]];
  for(; i < n; ++i){
    if(a[mp[i]] - pre == c){
      pre = a[mp[i]];
    }
    else{
      if(cnt){
        --cnt;
        ret = mp[i] + 1;
      }
      else{
        return -1;
      }
    }
  }
  if(cnt)ret = n;
  return ret;
}

int main(){
  cin >> n;
  if(n <= 2){
    cout << 1 << endl;
  }
  else{
    mp.clear();
    for(int i = 0; i < n; ++i)
      cin >> a[i],mp.push_back(i);
    sort(mp.begin(),mp.end(),[&](int x , int y){
      return a[x] < a[y];
    });
    if(deleteFirst()){
      cout << mp[0] + 1 << endl;
    }
    else if(deleteSecond()){
      cout << mp[1] + 1 << endl;
    }
    else{
      cout << check() << endl;
    }
  }
}
