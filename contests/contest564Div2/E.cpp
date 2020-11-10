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
const int maxn=2e5+10;
const int M=3005;
const int mod=998244353;
int n,m;
int a[maxn],w[maxn],g[M][M],f[M][M],inv[M<<2];

/*
extremely hard problem
fw[i][j][k]=expected weight of pic with ini weight w after i rounds and sum_like=j & sum_dislike=k
fw[i][j][k]=(w/(j+k))*fw+1[i-1][j+1][k]+((j-w)/(j+k))*fw[i-1][j+1][k]+(k/(j+k))*fw[i-1][j][k-1]
gw[i][j][k]=(k/(j+k))*fw-1[i-1][j][k-1]+((j-k)/(j+k))*fw[i-1][j][k-1]+(j/(j+k))*fw[i-1][j+1][k]

*/

int qpow(int x,int y){//x^y
	int ret=1;
	while(y){
		if(y&1)ret=(ll)ret*x%mod;
		x=(ll)x*x%mod;
		y>>=1;
	}
	return ret;
}

int main(){
	scanf("%d %d",&n,&m);
	for(int i=1;i<=n;++i){
		scanf("%d",a+i);
	}
	int sum[3];
	for(int i=1;i<=n;++i){
		scanf("%d",w+i);
		sum[a[i]]+=w[i];
		sum[2]+=w[i];
	}
	for(int i=max(0,m-sum[0]);i<=2*m;++i)inv[i]=qpow(sum[2]+i-m,mod-2),printf("inv[%d]=%d\n",sum[2]+i-m,inv[i]);//scale
	return 0;
}