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
#include <unordered_map>
#define REP(i,a,b) for(int i=a;i<b;i++)
#define RREP(i,a,b) for(int i=a;i>=b;i--)
#define FILL(a,b) memset(a,b,sizeof(a))
#define PB push_back
using namespace std;
typedef pair<int,int> ii;
typedef long long ll;
const int maxn=1e6+10;
string s1,s2;
int n,m;
ll dp[maxn][3][3];
int p1[maxn],p2[maxn];
/*
(x,y) is reachable iff 
1. s1[0...x+1] is not a subsequence of s2[0...y]
2. s2[0...y+1] is not a subsequence of s1[0...x]
3. not of the form : s1[0...x]=...ab and s2[0...y]=...ba
task is to count how many (x,y) satisfy
all these 3 conditions
*/

int f(char a){
	return a=='G'?0:(a=='R'?1:2);
}

void init(const string s,int n,const string t,int m,int p[]){
	p[0]=0;
	while(p[0]<m&&s[0]!=t[p[0]])
		p[0]++;
	p[0]=min(p[0],m-1);
	REP(i,1,n){
		p[i]=p[i-1]+1;
		while(p[i]<m&&s[i]!=t[p[i]])
			p[i]++;
		p[i]=min(p[i],m-1);
	}
}

int main(){
	cin>>s1;
	cin>>s2;
	n=s1.size();
	m=s2.size();
	init(s1,n,s2,m,p1);
	init(s2,m,s1,n,p2);
	FILL(dp,0ll);
	REP(i,1,m){
		REP(j,0,3){
			REP(k,0,3){
				if(f(s2[i-1])==j&&f(s2[i])==k)
					dp[i][j][k]=dp[i-1][j][k]+1;
				else 
					dp[i][j][k]=dp[i-1][j][k];
				//printf("(%d,%d,%d)=%lld\n",i,j,k,dp[i][j][k]);
			}
		}
	}
	ll ret=0;
	int l=0,r;
	//REP(i,0,n)printf("p1[%d]=%d\n",i,p1[i]);
	REP(i,0,n){
		r=p1[i];
		while(l<m&&p2[l]<i)l++;
		//printf("%d %d\n",l,r);
		ret+=max(r-l+1,0);
		if(i&&l<=r){
			int j=f(s1[i-1]),k=f(s1[i]);
			if(j!=k){
				ret-=dp[r][k][j];
				if(l-1>=0)ret+=dp[l-1][k][j];
			}
		}
	}
	cout<<ret<<endl;
	return 0;
}






