#include <iostream>
#include <cstring>
#include <vector>
#include <string.h>
//#include <bis/stdc++.h>
using namespace std;

const int maxn = 2e5 + 10;
int N , K , vis[maxn << 1];
char s[maxn << 1];

bool check1(){
  for(int i = 2; i <= 2 * N; ++i){
    if(s[i] == s[i - 1])return false;
  }
  return true;
}

bool check2(){
  for(int i = 2; i <= 2 * N; ++i){
    if(s[i] != s[i - 1])return false;
  }
  return true;
}

void solve(int l , int r){
  if(l == r){
    s[l] = s[l - 1];
  }
  else{
    char lc = s[l - 1] , rc = s[r + 1];
    for(int i = 1; i <= K && l <= r; ++i){
      s[l] = lc , s[r] = rc;
      ++l , --r;
    }
    if(l <= r && (K & 1)){
      for(int i = l; i <= r; ++i){
        if(s[i] == 'W')s[i] = 'B';
        else s[i] = 'W';
      }
    }
  }
}

int main(){
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cin >> N >> K;
  cin >> (s + 1);
  for(int i = 1; i <= N; ++i)s[i + N] = s[i];
  if(check1()){ //alternating
    if(K & 1){
      for(int i = 1; i <= N; ++i){
        if(s[i] == 'W')s[i] = 'B';
        else s[i] = 'W';
      }
    }
    for(int i = 1; i <= N; ++i)cout << s[i];
    cout << endl;
  }
  else if(check2()){ //all the same
    for(int i = 1; i <= N; ++i)cout << s[i];
    cout << endl;
  }
  else{ // finicky case
    memset(vis , 0 , sizeof(vis));
    for(int i = 2; i <= 2 * N; ++i){
      if(s[i] == s[i - 1])vis[i] = vis[i - 1] = 1;
    }
    if(s[1] == s[N])
      vis[1] = vis[N] = vis[N + 1] = vis[2 * N] = 1; //circular
    int pos = 0;
    for(int i = 1; i <= N; ++i){
      if(vis[i]){
        pos = i;
        break;
      }
    }
    for(int i = pos + 1 , l = -1 , r = -1; i <= N + pos; ++i){
      if(!vis[i]){
        if(l == -1)l = i;
        r = i;
      }
      else{
        if(l != -1)solve(l , r);
        l = r = -1;
      }
    }
    for(int i = N + 1; i <= N + pos - 1; ++i)cout << s[i];
    for(int i = pos; i <= N; ++i)cout << s[i];
    cout << endl;
  }
}
