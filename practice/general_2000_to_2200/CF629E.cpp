#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int maxn = 1e5 + 10;
int N , M , dep[maxn] , sz[maxn] , L , up[maxn][25] , tin[maxn] , tout[maxn] , timmer = 0;
ll DP[maxn] , DP2[maxn]; 
vector<int> g[maxn];

void DFS(int v , int p , int d){   
    tin[v] = ++timmer; 
    sz[v] = 1;
    dep[v] = d;
    up[v][0] = p;
    for(int i = 1; i <= L; ++i){
        up[v][i] = up[up[v][i - 1]][i - 1];
    }
    for(int u : g[v]){
        if(u == p)continue;
        DFS(u , v , d + 1);
        sz[v] += sz[u];
        DP[v] += DP[u] + sz[u];
    }
    tout[v] = ++timmer;
}

void DFS2(int v , int p){
    for(int u : g[v]){
        if(u == p)continue;
        DP2[u] = DP2[v] + (N - sz[u]) + DP[v] - (DP[u] + sz[u]);
        DFS2(u , v);
    }
}

bool isAncestor(int u , int v){ // check if u is v's ancestor
    return tin[u] <= tin[v] && tout[u] >= tout[v];
}

int lca(int u, int v){
    if(isAncestor(u , v))return u;
    if(isAncestor(v , u))return v;
    for(int i = L; i >= 0; --i){
        if(!isAncestor(up[u][i] , v))
            u = up[u][i];
    }
    return up[u][0];
}

int plca(int u , int v){
    for(int i = L; i >= 0; --i){
        if(!isAncestor(up[u][i] , v))
            u = up[u][i];
    }
    return u;
}

double solve(int u , int v){
    int x = lca(u , v);
    double ret = 0;
    ret = dep[u] + dep[v] - 2 * dep[x] + 1;
    if(x == u){
        int px = v;
        for(int i = L; i >= 0; --i){
            if(!isAncestor(up[px][i] , u) && up[px][i] != u){
                px = up[px][i];
            }
        }
        //ret += ((double)DP[v] * (N - sz[px]) + (DP2[u] + DP[u] - DP[px] - sz[px]) * sz[v]) / (sz[v] * (N - sz[px]));
        ret += 1.0 * DP[v] / sz[v] + (1.0 * DP2[u] + DP[u] - DP[px] - sz[px]) / (N - sz[px]);
    }
    else if(x == v){
        int px = u;
        for(int i = L; i >= 0; --i){
            if(!isAncestor(up[px][i] , v) && up[px][i] != v){
                px = up[px][i];
            }
        }
        //ret += ((double)DP[u] * (N - sz[px]) + (DP2[v] + DP[v] - DP[px] - sz[px]) * sz[u]) / (sz[u] * (N - sz[px]));
        ret += 1.0 * DP[u] / sz[u] + (1.0 * DP2[v] + DP[v] - DP[px] - sz[px]) / (N - sz[px]);
    }
    else{
        //ret = ((double)DP[u] * sz[v] + DP[v] * sz[u]) / (sz[u] * sz[v]);
        ret += 1.0 * DP[u] / sz[u] + 1.0 * DP[v] / sz[v];
    }
    return ret;
}

int main(){
    scanf("%d %d" , &N , &M);
    for(int i = 1; i < N; ++i){
        int u , v;
        scanf("%d %d" , &u , &v);
        g[u].push_back(v);
        g[v].push_back(u);
    }
    L = ceil(log2(N));
    DFS(1 , 1 , 1);
    DFS2(1 , 1);
    for(int i = 1; i <= M; ++i){
        int u , v;
        scanf("%d %d" , &u , &v);
        printf("%lf\n" , solve(u , v));
    }
}