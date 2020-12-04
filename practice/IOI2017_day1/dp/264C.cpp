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
const int maxn=1e5+10;
const ll INF=1e18;
int n,q;
ll dp[maxn],c[maxn],v[maxn];
//q<=500 , n<=10^5 => O(qnlogn) will TLE
//dp[i]=maximal score of the sequence ending with colour i 
//dp[i]=max{v[i]*a+dp[i] , v[i]*b+Maximal value st seq doest not end with c[i] , v[i]*b}
int main(){
	ll c1,c2,c3,c4;
	scanf("%d %d",&n,&q);
	REP(i,0,n)cin>>v[i];
	REP(i,0,n)cin>>c[i];
	REP(i,0,q){
		ll a,b;
		cin>>a>>b;
		ll mx1=-INF,mx2=-INF,ret=0;
		int pos1=0,pos2=0;
		REP(j,0,maxn)dp[j]=-INF;
		REP(j,0,n){
			c1=v[j]*b;
			c2=v[j]*a+dp[c[j]];
			if(c[pos1]==c[j])
				c3=mx2+v[j]*b;
			else 
				c3=mx1+v[j]*b;
			c4=dp[c[j]];
			dp[c[j]]=max(max(c1,c2),max(c3,c4));
			if(dp[c[j]]>mx1){
				if(c[j]==c[pos1]){
					mx1=dp[c[j]];
					pos1=j;
				}
				else{
					mx2=mx1;
					pos2=pos1;
					mx1=dp[c[j]];
					pos1=j;
				}
				ret=max(ret,mx1);
			}
			else if(dp[c[j]]>mx2){
				if(c[j]!=c[pos1]){
					mx2=dp[c[j]];
					pos2=j;
				}
			}
		}	
		cout<<ret<<endl;
	}
	return 0;
}