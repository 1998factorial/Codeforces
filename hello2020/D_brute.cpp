#include <iostream>
#include <algorithm>
using namespace std;
typedef pair<int , int> ii;

int N;
ii A[1005] , B[1005];

bool overlap(ii* C , int i , int j){
  return max(C[i].first , C[j].first) <= min(C[i].second , C[j].second);
}

bool solve(){
  for(int i = 1; i <= N; ++i){
    for(int j = i + 1; j <= N; ++j){
      if(!overlap(A , i , j) && overlap(B , i , j))return false;
      if(overlap(A , i , j) && !overlap(B , i , j))return false;
    }
  }
  return true;
}

int main(){
  cin >> N;
  for(int i = 1; i <= N; ++i){
    cin >> A[i].first >> A[i].second >> B[i].first >> B[i].second;
  }
  if(solve()){
    cout << "YES" << endl;
  }
  else{
    cout << "NO" << endl;
  }
}
