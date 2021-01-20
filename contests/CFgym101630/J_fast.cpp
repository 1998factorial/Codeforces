#include <bits/stdc++.h>
#define ID if(0)
using namespace std;
typedef long long ll;
const ll INF = 1e18;
const int maxn = 3005;
int N , M , K , fa[maxn];
vector<array<int , 2>> g[maxn] , g2[maxn];
array<int , 3> edges[maxn];
ll dis[maxn];
bool vis[maxn];

ll solve(int lim){
    for(int i = 1; i <= N; ++i)g2[i].clear() , dis[i] = INF , vis[i] = 0;
    for(int v = 1; v <= N; ++v){
        for(auto& e : g[v]){
            int nv = e[0] , w = e[1];
            w = max(0 , w - lim);
            g2[v].push_back({nv , w});
        }
    }
    dis[1] = 0;
    priority_queue<array<ll , 2> , vector<array<ll , 2>> , greater<array<ll , 2>>> q;
    q.push({dis[1] , 1});
    while(!q.empty()){
        auto cur = q.top();
        q.pop();
        ll d = cur[0];
        int v = cur[1];
        if(vis[v])continue;
        vis[v] = 1;
        for(auto& e : g2[v]){
            int nv = e[0] , w = e[1];
            if(vis[nv])continue;
            if(dis[nv] > dis[v] + w){
                dis[nv] = dis[v] + w;
                q.push({dis[nv] , nv});
            }
        }
    }
    return dis[N] + (ll)K * lim;
}

int main(){
    scanf("%d %d %d" , &N , &M , &K);
    for(int i = 1; i <= M; ++i) {
        int u , v , w;
        scanf("%d %d %d" , &u , &v , &w);
        g[u].push_back({v , w});
        g[v].push_back({u , w});
        edges[i] = {w , u , v};
    }
    // use Bellman-ford to solve for length <= K
    vector<vector<ll>> DP(N + 1 , vector<ll>(N + 1 , INF));
    DP[0][1] = 0;
    for(int i = 1; i <= min(K , N - 1); ++i){
        for(int v = 1; v <= N; ++v){
            for(auto& e : g[v]){
                int nv = e[0] , w = e[1];
                if(DP[i][v] > DP[i - 1][nv] + w){
                    DP[i][v] = DP[i - 1][nv] + w;
                }
            }
        }
    }
    ll ret = INF;
    for(int i = 0; i <= min(K , N - 1); ++i){
        ret = min(ret , DP[i][N]);
    }
    // NOW we solve the length > K
    // we fix the K-th edge weight
    // and we run dijstra on Gx
    sort(edges + 1 , edges + 1 + M);
    for(int i = 1; i <= M; ++i){
        ID printf("fixing w = %d\n" , edges[i][0]);
        ret = min(ret , solve(edges[i][0]));
    }
    printf("%lld\n" , ret);
}   