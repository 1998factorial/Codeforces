#include <cstdio>
#include <iostream>
#include <sstream>
#include <cstring>
#include <algorithm>
#include <vector>
#include <stack>
#include <queue>
#include <set>
#include <map>
#include <complex>
#include <unordered_set>
#define REP(i,a,b) for(int i=a;i<b;i++)
#define RREP(i,a,b) for(int i=a;i>=b;i--)
#define FILL(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef pair<int,int> ii;
typedef long long ll;
const int maxn=1e6+10;
const int mod=1e9+7;
int n,cnt[20][2];
int dp[maxn][21][2];
//dp[i][j][k]= # of good permutation up to ith place where gcd=2^j * 3^k
/*
n|1|2|3|4|5|6|7|8|9|10|
#|1|2|2|3|3|3|3|4|4|4|
-> 2^(i-1)<=p<2^i then #=i
由于n最大为1000000，故需要On或者Onlogn的算法
考虑合法排列的第一个元素。
为使fp最大，（经过打表），猜测开头元素是2^x * 3^y
且y最大为1
*/
int main(){
	scanf("%d",&n);
	int xn=0,yn=0;
	int N=n;
	while(N)N/=2,xn++;
	xn--;
	REP(i,1,n+1)
		REP(j,0,xn+1)
			REP(k,0,2)
				dp[i][j][k]=0;
	dp[1][xn][0]=1;
	if((1<<(xn-1))*3<=n)dp[1][xn-1][1]=1;
	int p=1;
	cnt[0][0]=n;
	cnt[0][1]=n/3;
	REP(i,1,20){
		p<<=1;
		REP(j,0,2){
			cnt[i][j]=n/p;
			p*=3;
		}
		p/=9;
	}
	REP(i,1,n){
		REP(j,0,xn+1){
			REP(k,0,2){
				//printf("dp[%d][%d][%d]=%lld\n",i,j,k,dp[i][j][k]);
				if(dp[i][j][k]){
					dp[i+1][j][k]=(dp[i+1][j][k]+1ll*dp[i][j][k]*(cnt[j][k]-i))%mod;
					if(j-1>=0)dp[i+1][j-1][k]=(dp[i+1][j-1][k]+1ll*dp[i][j][k]*(cnt[j-1][k]-cnt[j][k]))%mod;
					if(k-1>=0)dp[i+1][j][k-1]=(dp[i+1][j][k-1]+1ll*dp[i][j][k]*(cnt[j][k-1]-cnt[j][k]))%mod;
				}
			}
		}
	}
	printf("%d\n",dp[n][0][0]);
	return 0;
}