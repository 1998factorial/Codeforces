#include <iostream>
#include <cstring>
#include <vector>
using namespace std;

int Q;
int a , b;
string s;
vector<int> cnt[4];

// types of ... that we want
// 1. b <= l < a
// 2. a <= l < 2b
// 3. 2b <= l

bool check(int x){
  return x < b;
}

bool check1(int x){
  return b <= x && x < a;
}

bool check2(int x){
  return a <= x && x < 2 * b;
}

bool check3(int x){
  return b * 2 <= x;
}

int main(){
  cin >> Q;
  for(int q = 1; q <= Q; ++q){
    cin >> a >> b;
    cin >> s;
    for(int i = 1; i < 4; ++i)cnt[i].clear();
    int n = s.size();
    int i = 0;
    while(i < n){
      while(i < n && s[i] == 'X')++i;
      int j = i;
      while(j < n && s[j] == '.')++j;
      int l = j - i;
      if(b <= l && l < a)cnt[1].push_back(l);
      else if(a <= l && l < 2 * b)cnt[2].push_back(l);
      else if(l >= 2 * b)cnt[3].push_back(l);
      i = j + 1;
    }
    if(cnt[1].size() > 0 || cnt[3].size() > 1){
      cout << "NO\n"; // BOB can force a win here
    }
    else{
      if(cnt[3].size() == 0){
        if(cnt[2].size() % 2 == 1)cout << "YES\n"; // Alice win as she starts first
        else cout << "NO\n";
      }
      else{
        bool bad = true;
        bool t21 = false;
        bool t22 = false;
        for(int i = 1; i + a - 1 <= cnt[3][0]; ++i){
          int x = i - 1 , y = cnt[3][0] - a - i + 1;
          if(check(x) && check(y))bad = false , t21 = true;
          if(check2(x) && check2(y))t21 = true , bad = false;
          if(check(x) && check2(y))t22 = true , bad = false;
          if(check(y) && check2(x))t22 = true , bad = false;
        }
        if(bad){
          cout << "NO\n"; // no matter what Alice do , she is always going to generate case 1 or 3
        }
        else{
          if(cnt[2].size() % 2 == 0){
            if(t21)cout << "YES\n";
            else cout << "NO\n";
          }
          else{
            if(t22)cout << "YES\n";
            else cout << "NO\n";
          }
        }
      }
    }
  }
  return 0;
}
