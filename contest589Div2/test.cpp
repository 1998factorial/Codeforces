#include <iostream>
#include <time.h>
#include <set>
#include <unordered_map>
using namespace std;

int main(){
  int n , m;
  cin >> n >> m;
  srand(time(NULL));
  set<pair<int , int >> e;
  unordered_map<int , unordered_map<int , int >> mp;
  for(int i = 1; i <= m * 2; ++i){
    int x = rand() % n + 1;
    int y = rand() % n + 1;
    if(mp[x][y] == 0 && x != y){
      mp[x][y]++;
      mp[y][x]++;
      e.insert(make_pair(x , y));
    }
  }
  cout << n << " " << e.size() << endl;
  for(auto i : e){
    cout << i.first << " " << i.second << endl;
  }
  return 0;
}
