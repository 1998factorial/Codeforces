#include <iostream>
#include <cstdio>
#include <string>
#include <sstream> 
#include <vector>
#include <set>
#include <map>
#include <queue>
#include <stack>
#include <cmath>
#include <algorithm>
#include <cstring>
#include <ctime>
#include <cassert>
using namespace std;
const int maxn=55;
int L[maxn],R[maxn],X[maxn],C[maxn],dp[maxn][maxn][maxn],n,H,m;
//dp[i][j][k]=maximal profit for range [i..j] where tallest building is at most k
//easy to think of state as it is just a 区间dp, but hard to implement
int main(){
	cin>>n>>H>>m;
	for(int i=0;i<m;i++)cin>>L[i]>>R[i]>>X[i]>>C[i];
	memset(dp,0,sizeof(dp));
	for(int k=1;k<=H;k++){
		for(int len=1;len<=n;len++){
			for(int i=1;i+len-1<=n;i++){
				int j=i+len-1;
				dp[i][j][k]=dp[i][j][k-1];
				for(int pos=i;pos<=j;pos++){
					int s=k*k+dp[i][pos-1][k]+dp[pos+1][j][k];
					for(int q=0;q<m;q++){
						if(i<=L[q]&&j>=R[q]&&pos>=L[q]&&pos<=R[q]&&k>X[q])s-=C[q];
						//only pay fine once => only pay when (lq,rq) in (i,j) and lq<=pos<=rq and k > Height[q]
					}
					dp[i][j][k]=max(dp[i][j][k],s);
				}
			}
		}
	}cout<<dp[1][n][H]<<endl;
	return 0;
}