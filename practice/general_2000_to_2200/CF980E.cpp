#include <bits/stdc++.h>
using namespace std;
const int maxn = 1e6 + 10;
int N , K , L;
vector<int> g[maxn];
bool vis[maxn];
int up[maxn][40];

// we should try to take as many big vertices as possible
// so, we should start from N, and then aim for N - 1, N - 2 and so on, until we have N - K vertices

void DFS(int v , int p){
    up[v][0] = p;
    for(int i = 1; i <= L; ++i){
        up[v][i] = up[up[v][i - 1]][i - 1];
    }
    for(int u : g[v]){
        if(u == p)continue;
        DFS(u , v);
    }
}

int main(){
    scanf("%d %d" , &N , &K);
    for(int i = 1; i < N; ++i){
        int u , v;
        scanf("%d %d" , &u , &v);
        g[v].push_back(u);
        g[u].push_back(v);
    }
    L = ceil(log2(N));
    DFS(N , N);
    vis[N] = 1;
    int cnt = N - K - 1;
    for(int v = N - 1; v >= 1; --v){
        if(vis[v])continue;
        int u = v;
        int len = 1; // u
        for(int i = L; i >= 0; --i){
            int nu = up[u][i];
            if(vis[nu])continue;
            u = nu;
            len += (1 << i);
        }
        if(len <= cnt){
            cnt -= len;
            int u = v;
            for(;;){
                vis[u] = 1;
                u = up[u][0];
                if(vis[u])break;
            }
        }
    }
    for(int v = 1; v <= N; ++v)
        if(!vis[v])
            printf("%d " , v);
    printf("\n");
}