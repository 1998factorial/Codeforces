#include <iostream>
#include <cstring>
#include <algorithm>
using namespace std;

string s , c;

int main(){
  int T;
  cin >> T;
  for(int t = 1;t <= T; ++t){
    cin >> s;
    cin >> c;
    string best = s;
    int found = 0 , n = s.size();
    for(int i = 0; i < s.size() && !found; ++i){
      int bi = -1;
      char val = s[i];
      for(int j = s.size() - 1; j > i; --j){
        if(val > s[j]){
          val = s[j] , bi = j;
        }
      }
      if(val != s[i]){
        found = 1;
        swap(best[i] , best[bi]);
      }
    }
    if(best >= c)cout << "---" << endl;
    else cout << best << endl;
  }
}
