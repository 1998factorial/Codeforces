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
typedef long long ll;
ll mod=998244353;
const int maxn=2e5+5;
int n;
vector<int> g[maxn];
ll dp[maxn][3];
/*
共n点，n-1边，记f(x)为包含x个leave的最小连通子图
求对于任意两个不同的关于leave的集合x与y，使得f(x)与f(y)不联通的数量
*/
/*
let dp[i][0]=i不与任何子节点相连方法数
let dp[i][1]=i与正好一个子节点相连方法数
(otherwise it is not a smallest subgraph that covers these leaves)
let dp[i][2]=i与至少两个子节点相连方法数
let dp[leaf][2]=1
*/

void DFS(int i){
	if(!g[i].size()){//leaf
		dp[i][2]=1ll;
	}
	else{
		dp[i][0]=1ll;
		for(int c : g[i]){
			DFS(c);
			ll nchoose=(dp[c][0]+dp[c][2]+mod)%mod;
			ll choose=(dp[c][1]+dp[c][2]+mod)%mod;
			dp[i][2]=((dp[i][2]*nchoose)%mod+(((dp[i][2]+dp[i][1])%mod) * choose)%mod)%mod;
			//选=>（已选至少两个+已选正好一个）x（选c的方法数），不选=>（已经至少两个）x（不选c的方法数）
			dp[i][1]=((dp[i][0]*(dp[c][1]+dp[c][2])%mod)%mod+(dp[i][1]*(dp[c][0]+dp[c][2]))%mod)%mod;
			dp[i][0]=(dp[i][0]*nchoose+mod)%mod;
		}
	}
}

int main(){
	cin>>n;for(int i=1;i<=n;i++)g[i].clear();
	for(int i=2;i<=n;i++){
		int x;cin>>x;g[x].push_back(i);
	}
	memset(dp,0ll,sizeof(dp));
	DFS(1);
	cout<<(dp[1][0]+dp[1][2])%mod<<endl;
	return 0;
}