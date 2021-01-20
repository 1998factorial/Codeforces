#include <bits/stdc++.h>
using namespace std;

const int maxn = 1e5 + 10;
int N , M , ok[maxn] , dfn[maxn] , cnt , vis[maxn] , ok2[maxn];
vector<array<int , 2>> g[maxn];

void DFS(int v){ // get DFS order, mark DFS tree
    dfn[v] = ++cnt;
    for(auto& e : g[v]){
        int nv = e[0] , id = e[1];
        if(dfn[nv] == 0){
            DFS(nv);
            ok[id] = 1;
        }
    }
}

void DFS2(int v){ // get best backedge
    vis[v] = 1;
    for(auto& e : g[v]){
        int nv = e[0] , id = e[1];
        if(vis[nv] == 0){
            DFS2(nv);
        }
    }
    int cur = N + 100;
    int eid = -1;
    for(auto& e : g[v]){
        int nv = e[0] , id = e[1];
        if(!ok[id]){
            if(cur > dfn[nv]){
                cur = dfn[nv];
                eid = id;
            }
        }
    }
    if(~eid){
        ok2[eid] = 1;
    }
}

array<int , 2> edges[maxn];

int main(){
    int t;
    scanf("%d" , &t);
    while(t--){
        scanf("%d %d" , &N , &M);
        cnt = 0;
        for(int i = 1; i <= N; ++i)g[i].clear() , dfn[i] = 0 , vis[i] = 0; 
        for(int i = 1; i <= M; ++i)ok[i] = 0 , ok2[i] = 0;
        for(int i = 1; i <= M; ++i){
            int u , v;
            scanf("%d %d" , &u , &v);
            edges[i] = {u , v};
            g[u].push_back({v , i});
        }
        DFS(1);  
        DFS2(1);
        vector<array<int , 2>> ans;
        for(int i = 1; i <= M; ++i){
            if(!ok[i] && !ok2[i]){
                ans.push_back(edges[i]);
            }
        }
        for(int i = 0; i < M - 2 * N; ++i){
            printf("%d %d\n" , ans[i][0] , ans[i][1]);
        }
    }
}
