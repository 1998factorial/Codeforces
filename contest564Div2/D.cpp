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
//#include <unordered_set>
#define REP(i,a,b) for(int i=a;i<b;i++)
#define RREP(i,a,b) for(int i=a;i>=b;i--)
#define FILL(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef pair<int,int> ii;
typedef long long ll;
const int maxn=2e5+10;
const ll mod=998244353;
int deg[maxn],n;
ll f[maxn];
//ans=n!*deg[1]!*deg[2]!*...*deg[n]!
int main(){
	scanf("%d",&n);
	f[0]=1ll;
	for(int i=1;i<n;i++){
		int u,v;
		scanf("%d %d",&u,&v);
		deg[u]++;
		deg[v]++;
		f[i]=(f[i-1]*i)%mod;
	}
	ll ret=1ll;
	for(int i=1;i<=n;++i)ret=(ret*f[deg[i]])%mod;
	ret=(ret*n)%mod;
	cout<<ret<<endl;
	return 0;
}
