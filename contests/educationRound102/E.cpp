#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll INF = 1e18;
const int maxn = 2e5 + 10;
int N , M;
vector<array<int , 2>> g[maxn];
ll dis[maxn][2][2];
bool vis[maxn][2][2];
// dis[v][i][j] = min distance to v , i => we have drop one edge , j => we have doubled one edge
// if we dropped some edge that is not maximal
// or if we doubled some edge that is not minimal
// then dis[v][i][j] will not be minimal, hence, will not appear 
// first in the priority queue (dijstra)

int main(){
    scanf("%d %d" , &N , &M);
    for(int i = 1; i <= M; ++i){
        int u , v , w;
        scanf("%d %d %d" , &u , &v , &w);
        g[u].push_back({v , w});
        g[v].push_back({u , w});
    }
    for(int v = 1; v <= N; ++v){
        for(int i = 0; i < 2; ++i){
            for(int j = 0; j < 2; ++j){
                dis[v][i][j] = INF;
            }
        }
    }
    dis[1][0][0] = 0;
    priority_queue<array<ll , 4> , vector<array<ll , 4>> , greater<array<ll , 4>>> q;
    q.push({dis[1][0][0] , 1 , 0 , 0});
    while(!q.empty()){
        auto cur = q.top();
        q.pop();
        ll d = cur[0];
        int v = cur[1] , i = cur[2] , j = cur[3];
        if(vis[v][i][j])continue;
        vis[v][i][j] = 1;
        for(auto& e : g[v]){
            int nv = e[0] , w = e[1];
            // normal edge
            if(dis[nv][i][j] > dis[v][i][j] + w){
                dis[nv][i][j] = dis[v][i][j] + w;
                q.push({dis[nv][i][j] , nv , i , j});
            }
            // double this edge
            if(!j && dis[nv][i][1 - j] > dis[v][i][j] + 2ll * w){
                dis[nv][i][1 - j] = dis[v][i][j] + 2ll * w;
                q.push({dis[nv][i][1 - j] , nv , i , 1 - j});
            }
            // remove this edge
            if(!i && dis[nv][1 - i][j] > dis[v][i][j]){
                dis[nv][1 - i][j] = dis[v][i][j];
                q.push({dis[nv][1 - i][j] , nv , 1 - i , j});
            }
            // do both ? 
            if(!i && !j && dis[nv][1 - i][1 - j] > dis[v][i][j] + w){
                dis[nv][1 - i][1 - j] = dis[v][i][j] + w;
                q.push({dis[nv][1 - i][1 - j] , nv , 1 - i , 1 - j});
            }
        }
    }
    for(int v = 2; v <= N; ++v){
        printf("%lld " , dis[v][1][1]);
    }
    printf("\n");
}