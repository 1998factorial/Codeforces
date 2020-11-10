#include <iostream>
#include <cstring>
#include <cstdio>
#include <vector>
using namespace std;

int N , K;
string s;
// N <= 2e5 , K <= 1e9


int main(){
  cin >> N >> K;
  cin >> s;
  int cnt = 0;
  for(int i = 0; i <= N; ++i){
    if(s[i % N] == s[(i - 1 + N) % N]){
      ++cnt;
    }
  }
  if(cnt > 0){
    string ss = s;
    int start = 0;
    while(start < N && s[start] != s[(start + 1) % N])++start;
    while(start < N && s[start] == s[(start + 1) % N])++start;
    ++start;
    vector<bool> vis(N , false);
    for(int i = start; i < N + start; ++i){
      if(vis[(i + N) % N])continue;
      if(s[(i + N) % N] != s[(i - 1 + N) % N] && s[(i + N) % N] != s[(i + 1 + N) % N]){
        // unstable
        int j = i;
        while(j < N + start && s[(j + N) % N] != s[(j - 1 + N) % N] && s[(j + N) % N] != s[(j + 1 + N) % N]){
          ++j;
        }
        for(int k = i; k < j; ++k){
          vis[(k + N) % N] = true;
        }
        int l = i , r = j - 1;
        int c = 0;
        while(l <= r && c <= K){
          if(c % 2 == 0){ //flip
            if((l + N) % N == (r + N) % N){
              if(s[(l + N) % N] == 'B')ss[(l + N) % N] = 'W';
              else ss[(l + N) % N] = 'B';
            }
            else{
              if(s[(l + N) % N] == 'B')ss[(l + N) % N] = 'W';
              else ss[(l + N) % N] = 'B';
              if(s[(r + N) % N] == 'B')ss[(r + N) % N] = 'W';
              else ss[(r + N) % N] = 'B';
            }
          }
          ++l; --r; ++c;
        }
        if(c % 2 == 0){
          while(l <= r){
            if((l + N) % N == (r + N) % N){
              if(s[(l + N) % N] == 'B')ss[(l + N) % N] = 'W';
              else ss[(l + N) % N] = 'B';
            }
            else{
              if(s[(l + N) % N] == 'B')ss[(l + N) % N] = 'W';
              else ss[(l + N) % N] = 'B';
              if(s[(r + N) % N] == 'B')ss[(r + N) % N] = 'W';
              else ss[(r + N) % N] = 'B';
            }
            ++l; --r;
          }
        }
      }
    }
    cout << ss << endl;
  }
  else{
    if(K % 2 == 0){
      cout << s << endl;
    }
    else{
      for(int i = 0; i < N; ++i){
        if(s[i] == 'B')
          cout << "W";
        else
          cout << "B";
      }
    }
  }
  return 0;
}
