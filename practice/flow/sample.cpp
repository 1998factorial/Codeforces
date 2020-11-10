/*
    Faster Dinic template
*/
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <queue>
#define FOR(i,a,b) for(int i=a;i<=b;++i)

const int N=1e5+5,M=5e6+5;
const int inf=1<<30;
int n,m,tot=1,lnk[N],ter[M],nxt[M],val[M],dep[N],cnr[N];

int id(int x,int y) {
	return (x-1)*m+y;
}
void add(int u,int v,int w) {
	ter[++tot]=v,nxt[tot]=lnk[u],lnk[u]=tot,val[tot]=w;
}
void addedge(int u,int v,int w) {
	add(u,v,w),add(v,u,0);
}
int bfs(int s,int t) {
	memset(dep,0,sizeof(dep));
	memcpy(cnr,lnk,sizeof(lnk));
	std::queue<int> q;
	q.push(s),dep[s]=1;
	while(!q.empty()) {
		int u=q.front(); q.pop();
		for(int i=lnk[u];i;i=nxt[i]) {
			int v=ter[i];
			if(val[i]&&!dep[v]) q.push(v),dep[v]=dep[u]+1;
		}
	}
	return dep[t];
}
int dfs(int u,int t,int flow) {
	if(u==t) return flow;
	int ans=0;
	for(int i=cnr[u];i&&ans<flow;i=nxt[i]) {
		cnr[u]=i;
		int v=ter[i];
		if(val[i]&&dep[v]==dep[u]+1) {
			int x=dfs(v,t,std::min(val[i],flow-ans));
			if(x) val[i]-=x,val[i^1]+=x,ans+=x;
		}
	}
	if(ans<flow) dep[u]=-1;
	return ans;
}
int dinic(int s,int t) {
	int ans=0;
	while(bfs(s,t)) {
		int x;
		while((x=dfs(s,t,inf))) ans+=x;
	}
	return ans;
}
int main() {
	scanf("%d%d",&n,&m);
	int s=0,t=5*n*m+3,cnt=n*m;//t=n*m+2*n*(m-1)+2*(n-1)*m+1,cnt=n*m;
	int ans=0;
	FOR(i,1,n) FOR(j,1,m) {
		int x;
		scanf("%d",&x),ans+=x;
		addedge(s,id(i,j),x);
	}
	FOR(i,1,n) FOR(j,1,m) {
		int x;
		scanf("%d",&x),ans+=x;
		addedge(id(i,j),t,x);
	}
	FOR(i,1,n-1) FOR(j,1,m) {
		int x;
		scanf("%d",&x),ans+=x;
		addedge(s,++cnt,x);
		addedge(cnt,id(i,j),inf);
		addedge(cnt,id(i+1,j),inf);
	}
	FOR(i,1,n-1) FOR(j,1,m) {
		int x;
		scanf("%d",&x),ans+=x;
		addedge(++cnt,t,x);
		addedge(id(i,j),cnt,inf);
		addedge(id(i+1,j),cnt,inf);
	}
	FOR(i,1,n) FOR(j,1,m-1) {
		int x;
		scanf("%d",&x),ans+=x;
		addedge(s,++cnt,x);
		addedge(cnt,id(i,j),inf);
		addedge(cnt,id(i,j+1),inf);
	}
	FOR(i,1,n) FOR(j,1,m-1) {
		int x;
		scanf("%d",&x),ans+=x;
		addedge(++cnt,t,x);
		addedge(id(i,j),cnt,inf);
		addedge(id(i,j+1),cnt,inf);
	}
	printf("%d\n",ans-dinic(s,t));
	return 0;
}
