#include <bits/stdc++.h>
#define MAX_SIZE 3505
typedef long long ll;
#define INF 100000000000
using namespace std;

struct Maxflow {
    struct edge {
    	int from, to;
    	ll flow, capacity;
    };
    
    // start and end point
    int s, t;
    
    // list array
    vector<edge> edg;
    
    // g reference to the ith vertex's edges
    vector<int> g[MAX_SIZE];
    
    // distance array and visited array
    int dist[MAX_SIZE], visited[MAX_SIZE];
    int cur[MAX_SIZE];
    
    void init() {
    	edg.clear();
    	int i;
    	for (i = 0 ; i < MAX_SIZE; i++) {
    		g[i].clear();
    	}
    }
    
    void addedge(int from, int to, ll capacity) {
    	edge e1 = edge{from, to, 0ll, capacity};
    	edge e2 = edge{to, from, 0ll, 0ll};
    	edg.push_back(e1), edg.push_back(e2);
    	g[from].push_back((int) edg.size() - 2);
    	g[to].push_back((int) edg.size() - 1);
    }
    
    // construct the level graph
    bool bfs() {
    	memset(visited,0,sizeof(visited));
    	memset(dist,0,sizeof(dist));
    	queue<int> q;
    	q.push(s);
    	visited[s] = 1;
    	dist[s] = 0;
    	while (!q.empty()) {
    		int v = q.front();
    		q.pop();
    		for (int i = 0 ; i < (int) g[v].size(); i++) {
    			edge &e = edg[g[v][i]];
    			int nxt = e.to;
    			if (!visited[nxt] && e.capacity > e.flow) {
    				dist[nxt] = dist[v] + 1;
    				q.push(nxt);
    				visited[nxt] = 1;
    			}  
    		}
    	}
    	
    	return visited[t];
    }
    
    ll dfs(int x, ll cp) {
    	if (x == t || cp == 0) {
    		return cp;
    	}
    	
    	ll flow = 0, newflow;
    	for (int &y = cur[x]; y < (int) g[x].size(); y++) {
    		edge &e = edg[g[x][y]];
    		if (dist[x] + 1 == dist[e.to]) {
    			ll minn = min(cp, e.capacity - e.flow);
    			newflow = dfs(e.to, minn);
    			if (newflow > 0) {
    				e.flow += newflow;
    				edg[g[x][y] ^1].flow -= newflow;
    				flow += newflow;
    				cp -= newflow;
    				
    				if (cp == 0) {
    					break;
    				}
    			}
    		}
    	}
    	
    	return flow;
    }
    
    ll Dinic(){
        ll flow=0;
        while(bfs()){
            memset(cur,0,sizeof(cur));
            flow += dfs(s,INF);
        }
        return flow;
    }
};
 
int N , a[MAX_SIZE] , b[MAX_SIZE];
 
// maximal enclosure graph
 
int main(){
    int ret = 0;
    scanf("%d" , &N);
    for(int i = 1; i <= N; ++i){
        scanf("%d" , &a[i]);
    }
    for(int i = 1; i <= N; ++i){
        scanf("%d" , &b[i]);
        ret += max(0 , b[i]);
    }
    Maxflow solver;
    solver.init();
    solver.s = N + 7 , solver.t = N + 8;
    for(int i = 1; i <= N; ++i){
        if(b[i] >= 0){
            solver.addedge(solver.s , i , b[i]);
        }
        else{
            solver.addedge(i , solver.t , -b[i]);
        }
        set<int> vis;
        // use transitvity of divsibility
        // avoid a -> b -> c and additional a -> c
        for(int j = i - 1; j >= 1; --j){
            if(a[i] % a[j] == 0){
                int ok = 1;
                for(int k : vis){
                    if(k % a[j] == 0)ok = 0;
                }
                if(ok)solver.addedge(i , j , INF);
                vis.insert(a[j]);
            }
        }
    }
    int max_flow = solver.Dinic();
    printf("%d\n" , ret - max_flow);
}   
