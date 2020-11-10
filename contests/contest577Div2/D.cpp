#include <iostream>
#include <cstring>
#include <algorithm>
#include <cstdio>
#include <vector>
#include <set>
using namespace std;
typedef long long ll;
int n,m,k,q;
const int maxn = 2e5 + 10;
int pos[maxn][2]; // positions of the treasure
int goodcol[maxn]; // safe column where we can move up
int L[maxn],R[maxn];
int tL[maxn],tR[maxn]; // tL[i] = col of the left most treasure on row i
// L[i] = the cloest safe col when we go left from col[i]
// similar for R[i]
ll dp[maxn][2][2];
// dp[i][0][0] = min num of steps to collect all treasures from row 1 to i
// where our last position is on left and heading to left
int main(){
  cin >> n >> m >> k >> q;
  for(int i = 1; i <= k; ++i)
    cin >> pos[i][0] >> pos[i][1];
  for(int i = 1; i <= n; ++i)
    tL[i] = m + 1, tR[i] = -1;
  for(int i = 1; i <= k; ++i){
    int r = pos[i][0];
    int c = pos[i][1];
    tL[r] = min(tL[r] , c);
    tR[r] = max(tR[r] , c);
  }
  for(int i = 1; i <= q; ++i)
    cin >> goodcol[i];
  sort(goodcol + 1, goodcol + 1 + q);
  memset(R,-1,sizeof(R));
  memset(L,-1,sizeof(L));
  for(int i = 1; i <= goodcol[1]; ++i){
    R[i] = goodcol[1]; // obvious
    //printf("R[%d] = %d\n",i , R[i]);
  }
  for(int i = 1; i < q; ++i){
    for(int j = goodcol[i] + 1; j <= goodcol[i + 1]; ++j){
      R[j] = goodcol[i + 1]; // obvious
      //printf("R[%d] = %d\n",j , R[j]);
    }
  }
  for(int i = m; i >= goodcol[q]; --i){
    L[i] = goodcol[q]; // will have to left
    //printf("L[%d] = %d\n",i,L[i]);
  }
  for(int i = q; i > 1; --i){
    for(int j = goodcol[i] - 1; j >= goodcol[i - 1]; --j){
      L[j] = goodcol[i - 1]; // obvious
      //printf("L[%d] = %d\n",j,L[j]);
    }
  }

}
