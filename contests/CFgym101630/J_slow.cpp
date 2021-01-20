#include <bits/stdc++.h>
#define ID if(0)
using namespace std;
typedef long long ll;
const ll INF = 1e18;
const int maxn = 3005;
int N , M , K , fa[maxn];
vector<array<int , 2>> g[maxn]; 
array<int , 3> edges[maxn];
// fix the k-th largest edge weight to be x
// for each edge whose weight < x are free
// make connected components using these free edges first
// we then find the smallest length = k path from CC contains 1 to CC
// contains N with bellman-ford

int find(int x){
    return fa[x] == x ? x : fa[x] = find(fa[x]);
}

void merge(int x , int y){
    x = find(x);
    y = find(y);
    fa[x] = y;
}

ll solve(int lim){
    // first , use union find to merge components
    for(int i = 1; i <= N; ++i)fa[i] = i;
    for(int i = 1; i < lim; ++i){
        int u = edges[i][1] , v = edges[i][2];
        merge(u , v);
    }
    if(find(1) == find(N))return INF;
    vector<vector<ll>> DP(N + 1 , vector<ll>(N + 1 , INF));
    for(int v = 1; v <= N; ++v){
        if(find(v) == find(1))DP[0][find(v)] = 0;
    }
    for(int i = 1; i <= min(N - 1 , K); ++i){
        for(int v = 1; v <= N; ++v){
            for(auto& e : g[v]){
                int nv = e[0] , w = e[1];
                if(find(nv) == find(v))continue;
                if(DP[i][find(v)] > DP[i - 1][find(nv)] + w){
                    DP[i][find(v)] = DP[i - 1][find(nv)] + w;
                }
            }
        }
    }  
    ID{  
        printf("for eid = %d\n" , lim);
        for(int i = 1; i <= min(N - 1 , K); ++i){
            for(int v = 1; v <= N; ++v){
                printf("DP[%d][%d] = %lld\n" , i , v,  DP[i][v]);
            }
        }
    }
    return DP[min(N - 1 , K)][N];
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
    sort(edges + 1 , edges + 1 + M);
    for(int i = 1; i <= M; ++i){
        ID printf("fixing w = %d\n" , edges[i][0]);
        ret = min(ret , solve(i));
    }
    printf("%lld\n" , ret);
}