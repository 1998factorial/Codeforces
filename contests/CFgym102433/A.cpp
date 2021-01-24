#include <bits/stdc++.h>
using namespace std;
#define lli long long int
#define MAXN 100005
#define ii pair<int, lli>
#define pb push_back
#define ID if (1)
 
int n, u, v, w;
lli t[MAXN];
vector<ii> e[MAXN];
map<int, map<int, lli>> d;
 
lli sumdist[MAXN];
lli sumt[MAXN];
lli dp[MAXN];
lli answer[MAXN];
lli sz[MAXN];
 
void dfs1(int at, int prev) {
	sumt[at] = t[at];
	sz[at] = 1;
	for (auto [next,w] : e[at]) {
		if (next==prev) continue;
		dfs1(next,at);
		sz[at]+=sz[next];
		sumdist[at]+=w*sz[next];
		sumdist[at]+=sumdist[next];
		sumt[at]+=sumt[next];
		dp[at]+=dp[next];
		dp[at]+=sumt[next]*w;
	}
}
 
// change root from a to b
void reroot(int a, int b) {
	lli w = d[a][b];
	sumdist[a]-=w*sz[b];
	sumdist[a]-=sumdist[b];
	sz[a]-=sz[b];
	sumt[a]-=sumt[b];
	dp[a]-=dp[b];
	dp[a]-=sumt[b]*w;
 
	sumdist[b]+=w*sz[a];
	sumdist[b]+=sumdist[a];
	sz[b]+=sz[a];
	sumt[b]+=sumt[a];
	dp[b]+=dp[a];
	dp[b]+=sumt[a]*w;
}
 
void dfs2(int at, int prev) {
	// calc answer for at
	answer[at] = (sumdist[at]*t[at])+dp[at];
	for (auto [next,w]: e[at]) {
		if (next==prev) continue;
		reroot(at,next);
		dfs2(next,at);
		reroot(next,at);
	}
}
 
int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
	cin >> n;
	for (int i = 1; i <= n; i++) cin >> t[i];
	for (int i = 2; i <= n; i++) {
		cin >> u >> v >> w;
		e[u].pb({v,w});
		e[v].pb({u,w});
		d[u][v] = w;
		d[v][u] = w;
	}
 
	dfs1(1, 0);
	dfs2(1, 0);
	for (int i = 1; i <= n; i++) cout << answer[i] << endl;
}