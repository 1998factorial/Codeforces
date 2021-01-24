#include <bits/stdc++.h>
#define MAX_SIZE 655
using namespace std;
typedef long long ll;
const ll INF = 1e13;
 
struct Maxflow {
    struct edge {
        int from, to;
        ll flow, capacity;
    };
 
    int s, t;
 
    vector<edge> edg;
 
    vector<int> g[MAX_SIZE];
 
    int dist[MAX_SIZE], visited[MAX_SIZE], cur[MAX_SIZE];
 
    void init() {
        edg.clear();
        int i;
        for (i = 0 ; i < MAX_SIZE; ++i) {
            g[i].clear();
        }
    }
 
    void addedge(int from, int to, ll capacity) {
        edge e1 = edge{from, to, 0ll, capacity};
        edge e2 = edge{to, from, 0ll, 0ll};
        edg.push_back(e1);
        edg.push_back(e2);
        g[from].push_back((int) edg.size() - 2);
        g[to].push_back((int) edg.size() - 1);
    }
 
    bool bfs() {
        memset(visited, 0, sizeof(visited));
        memset(dist, 0, sizeof(dist));
        queue<int> q;
        q.push(s);
        visited[s] = 1;
        dist[s] = 0;
        while (!q.empty()) {
            int v = q.front();
            q.pop();
            for (int i = 0 ; i < (int) g[v].size(); ++i) {
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
        if (x == t || cp == 0) return cp;
        ll flow = 0, newflow;
        for (int &y = cur[x]; y < (int) g[x].size(); ++y) {
            edge &e = edg[g[x][y]];
            if (dist[x] + 1 == dist[e.to]) {
                ll minn = min(cp, e.capacity - e.flow);
                newflow = dfs(e.to, minn);
                if (newflow > 0) {
                    e.flow += newflow;
                    edg[g[x][y] ^ 1].flow -= newflow;
                    flow += newflow;
                    cp -= newflow;
                    if (cp == 0) break;
                }
            }
        }
 
        return flow;
    }
 
    ll Dinic() {
        ll flow = 0;
        while (bfs()) {
            memset(cur, 0, sizeof(cur));
            flow += dfs(s, INF);
        }
        return flow;
    }
};

Maxflow solver;
int N , L;
char str[MAX_SIZE][MAX_SIZE];
int colour[MAX_SIZE];
vector<int> graph[MAX_SIZE];
bool vis[MAX_SIZE];
void DFS(int v , int p , int c){
    colour[v] = c;
    vis[v] = 1;
    for(int nv : graph[v]){
        if(nv == p || vis[nv])continue;
        DFS(nv , v , c ^ 1);
    }
}
int main(){
    scanf("%d" , &N);
    for(int i = 1; i <= N; ++i){
        scanf("%s" , str[i] + 1);
    }
    L = strlen(str[1] + 1);
    int s = MAX_SIZE - 5 , t = s - 1;
    solver.s = s; solver.t = t;
    for(int i = 1; i <= N; ++i){
        for(int j = 1; j <= N; ++j){
            if(i != j){
                int nd = 0;
                for(int k = 1; k <= L; ++k)nd += str[i][k] != str[j][k];
                if(nd == 2){
                    graph[i].push_back(j);
                }
            }
        }
    }
    for(int i = 1; i <= N; ++i){
        if(!vis[i]){
            DFS(i , i , 0);
        }
    }
    for(int i = 1; i <= N; ++i){
        if(!colour[i]){
            solver.addedge(s , i , 1ll);
            for(int nv : graph[i]){
            solver.addedge(i , nv , 1ll);
        }
        }
        else{
            solver.addedge(i , t , 1ll);
        }
    }
    ll r = solver.Dinic();
    printf("%lld\n" , N - r);
}