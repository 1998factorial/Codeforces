#include <algorithm>
#include <iostream>
#include <cstdio>
#include <cstring>
#include <sstream>
#define REP(i,a,b) for(int i=a;i<b;i++)
using namespace std;
typedef long long ll;

const int maxn=1e6+10;
char s1[maxn],s2[maxn];
ll dp[maxn][3][3];
int p1[maxn],p2[maxn],n,m;

int mp(char a){
	return a=='G'?0:(a=='R'?1:2);
}

void ini(const char a[],int n,const char b[],int m,int p[]){
	//p[i]=j <=> a[0..i] is a subseq of b[0..j]
	p[0]=0;
	REP(i,1,n+1){
		p[i]=p[i-1]+1;
		while(p[i]<=m&&a[i]!=b[p[i]])p[i]++;
		p[i]=min(p[i],m);
	}
}

int main(){
	scanf("%s",s1+1);
	scanf("%s",s2+1);
	n=strlen(s1+1);
	m=strlen(s2+1);
	ini(s1,n,s2,m,p1);//build injection
	ini(s2,m,s1,n,p2);
	memset(dp,0ll,sizeof(dp));
	REP(i,2,m+1){//compute s2
		REP(j,0,3){
			REP(k,0,3){
				if(mp(s2[i-1])==j&&mp(s2[i])==k)
					dp[i][j][k]=dp[i-1][j][k]+1;
				else
					dp[i][j][k]=dp[i-1][j][k];
				//printf("dp[%d][%d][%d]=%lld\n",i,j,k,dp[i][j][k]);
			}
		}
	}
	ll ret=0ll;
	int l=1,r;
	REP(i,1,n+1){
		//for each si in s1
		//find range of indices where is reachable
		r=p1[i];
		while(l<=m&&p2[l]<i)l++;
		ret+=max(r-l+1,0); //s2[l..r] is good state for s1[i]
		if(i>1&&l<=r){
			int j=mp(s1[i-1]);
			int k=mp(s1[i]);
			if(j!=k){
				ret-=dp[r][k][j];
				ret+=dp[l-1][k][j];
			}
		}
	}
	cout<<ret<<endl;
	return 0;
}