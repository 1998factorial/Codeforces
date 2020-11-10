#include <bits/stdc++.h>
#define x first 
#define y second
using namespace std;
typedef pair<int , int> ii;
const int INF = 1e9 + 10;
const int maxn = 5e5 + 10;
int N , M , DP[maxn][2];
vector<ii> g[maxn];

int main(){
    scanf("%d%d" , &N , &M);
    for(int i = 1; i <= M; ++i){
        int x , y , w;
        scanf("%d%d%d" , &x , &y , &w);
        g[y].emplace_back(x , w);
    }
    for(int i = 1; i <= N; ++i){
        for(int j = 0; j < 2; ++j){
            DP[i][j] = INF;
        }
    }
    DP[N][0] = DP[N][1] = 0;
    queue<int> q;
    q.push(N);
    while(!q.empty()){
        int v = q.front();
        q.pop();
        for(auto& e : g[v]){
            int nv = e.x , nt = e.y;
            if(DP[nv][nt] >= INF){ // optimal path must be simple path
                DP[nv][nt] = max(DP[v][0] , DP[v][1]) + 1;
                if(max(DP[nv][0] , DP[nv][1]) < INF){ // means nv is done with update
                    q.push(nv);
                }
            }
        }
    }
    if(max(DP[1][0] , DP[1][1]) >= INF)printf("-1\n");
    else printf("%d\n" , max(DP[1][0] , DP[1][1]));
    for(int i = 1; i <= N; ++i){
        if(DP[i][0] > DP[i][1])printf("0");
        else printf("1");
    }
    printf("\n");
}


/*
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
using ll = long long;
 
const int N = 5 * (int)1e5;
vector<int> conns[N][2];
vector<int> rev[N][2];
int ban[N];
 
int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);
 
	int n, m;
	cin >> n >> m;
 
	for (int i = 0; i < m; ++i) {
		int a, b, t;
		cin >> a >> b >> t;
		--a; --b;
		conns[a][t].push_back(b);
		rev[b][t].push_back(a);
	}
	for (int i = 0; i < n; ++i) ban[i] = -1;
 
	// From every node, there are 0-edges and 1-edges. We can delete either all outgoing 0-edges, or all outgoing 1-edges.
	// If a vertex has a 0-edge to the target, we want to delete 0-edges from it, and vice versa for 1-edges.
	// If we deleted outgoing edges from a vertex, we'll call it used. Otherwise, unused.
	// Some vertices have both 0-edges and 1-edges to the targets. We'll call those "distance 1 vertices".
	// If an unused vertex has edges to a distance 1 vertex, delete them. Define distance 2 vertices similarly. Repeat until
	// the source gets handled or there are no paths to the sink. Correctness is obvious: from every vertex, path to sink
	// is as long as it could be. Proof by induction: at every step, this holds for the "distance t vertices" we just created.
	// Queues and reverted edges should let us do this in linear time.
 
	vector<int> dist(n, n);
	dist[n-1] = 0;
	vector<int> que = {n-1};
	for (int ind = 0; ind < que.size(); ++ind) {
		int i = que[ind];
		for (int t = 0; t < 2; ++t) {
			for (int j : rev[i][t]) {
				if (ban[j] == -1) ban[j] = t;
				if (ban[j] != t && dist[j] > dist[i] + 1) {
					dist[j] = dist[i] + 1;
					que.push_back(j);
				}
			}
		}
	}
 
	if (dist[0] == n) cout << -1 << '\n';
	else cout << dist[0] << '\n';
	for (int i = 0; i < n; ++i) cout << (ban[i] != -1 ? (ban[i] ^ 1) : 0); cout << '\n';


*/