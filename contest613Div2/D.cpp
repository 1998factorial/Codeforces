#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

int N;

/*
  find min{max(a[1] ^ X , ... , a[N] ^ X)} for some X
  1 <= a[i] <= 2 ^ 30 - 1
  we can do this bit by bit (like a trie)
  if at some bit , all a[1 .. N] & (1 << bit) = 0 or 1
  we are certain that we can always make this bit 0
  else we can greedily keep going by splitting the array a into
  2 , where they are differed on this bit
  O(N * logN)
*/


int solve(vector<int>& a , int bit){
  if(a.size() == 0 || bit < 0)return 0;
  vector<int> L , R;
  for(int i : a){
    if(i & (1 << bit)) L.push_back(i);
    else R.push_back(i);
  }
  if(L.size() == 0)return solve(R , bit - 1);
  if(R.size() == 0)return solve(L , bit - 1);
  return min(solve(L , bit - 1) , solve(R , bit - 1)) + (1 << bit);
}

int main(){
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cin >> N;
  vector<int> a;
  for(int i = 1; i <= N; ++i){
    int x; cin >> x; a.push_back(x);
  }
  cout << solve(a , 30) << endl;
}
