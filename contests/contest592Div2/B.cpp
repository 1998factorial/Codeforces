#include <iostream>
#include <cstring>
#include <cstdio>
using namespace std;

int N;
string a;
bool vis[1005][2];

int DFS(int i , int j){
  vis[i][j] = true;
  int ret = 0;
  //right
  //if(j - 1 >= 0 && a[i] == '1' && !vis[i][j - 1])printf("(%d %d)->(%d %d)\n" , i , j , i , j - 1);
  if(i + 1 < N && !vis[i + 1][j])ret = max(ret , DFS(i + 1 , j));
  //left
  if(i - 1 >= 0 && !vis[i - 1][j])ret = max(ret , DFS(i - 1 , j));
  //up
  if(j + 1 < 2 && a[i] == '1' && !vis[i][j + 1])ret = max(ret , DFS(i , j + 1));
  //down
  if(j - 1 >= 0 && a[i] == '1' && !vis[i][j - 1])ret = max(ret , DFS(i , j - 1));
  vis[i][j] = false;
  return 1 + ret;
}


int main(){
  int T;
  cin >> T;
  for(int t = 1; t <= T; ++t){
    cin >> N;
    cin >> a;
    int ret = 0;
    for(int k = 0; k < N; ++k)vis[k][0] = vis[k][1] = false;
    //cout << DFS(0 , 0) << endl;
    for(int i = 0; i < N; ++i){
      for(int j = 0; j < 2; ++j){
        int rr = DFS(i , j);
        //printf("(%d , %d) = %d\n" , i , j  ,rr);
        ret = max(ret , DFS(i , j));
      }
    }
    cout << ret << endl;
  }
  return 0;
}
