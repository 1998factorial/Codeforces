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
struct ball{
	int c,v;
}s[maxn];
int n,q,a,b,dp[maxn][2];

int main(){
	scanf("%d %d",&n,&q);
	REP(i,0,n)scanf("%d",&s[i].v);
	REP(i,0,n)scanf("%d",&s[i].c);
	REP(i,0,q){
		scanf("%d %d",&a,&b);
		dp[0][1]=b*s[0].v;
		int ret=0;
		REP(i,1,n){
			dp[i][1]=b*s[i].v;
			dp[i][0]=-(1<<INF);
			REP(j,0,i){
				if(s[i].c==s[j].c)
					dp[i][1]=max(dp[i][1],dp[j][1]+a*s[i].v);
				else
					dp[i][1]=max(dp[i][1],dp[j][1]+b*s[i].v);
				dp[i][0]=max(dp[i][0],max(dp[j][0],dp[j][1]));
			}
			ret=max(ret,max(dp[i][0],dp[i][1]));
		}
		cout<<ret<<endl;
	}
	return 0;
}