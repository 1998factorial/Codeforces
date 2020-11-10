#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int l , r;
vector<int> a , b;
int len;
vector<int> path;

bool solve(int pos , int state , int flag){
  if(pos >= len){

  }
  else{
    int up = flag ? b[pos];
    for(){
      
    }
  }
}

int main(){
  cin >> l >> r;
  a.clear();
  b.clear();
  while(l){
    a.push_back(l % 10);
    l /= 10;
  }

  while(r){
    b.push_back(r % 10);
    r /= 10;
  }
  len = max((int)a.size() , (int)b.size());
  if(a.size() < b.size()){
    for(int i = 1; i <= b.size() - a.size(); ++i)a.push_back(0);
  }
  reverse(b.begin() , b.end());
  reverse(a.begin() , a.end());
  path.clear();
  if(solve( 0 , 0 , i == b[0]){
    return 0;
  }
  cout << -1 << endl;
  return 0;
}
