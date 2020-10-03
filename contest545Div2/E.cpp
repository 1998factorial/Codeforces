#pragma GCC optimize(3)
#pragma GCC optimize(2)
#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
#define DEBUG if(0)
using namespace std;
 
const int maxn = 1e5 + 5;
const int INF = 1e9;
vector<int> g[maxn * 51] , S , comp[maxn * 51] , G[maxn * 51];
int dfn[maxn * 51] , low[maxn * 51] , compID[maxn * 51] , compval[maxn * 51];
bool instack[maxn * 51];
char open[maxn][51];
int N , D , M , cnt = 0 , tot = 0;
 
inline int ID(int v , int d){
    return d * N + v;
}
 
void tarjan(int v){
    dfn[v] = low[v] = ++cnt;
    S.push_back(v);
    instack[v] = 1;
    for(int u : g[v]){
        if(dfn[u] == -1){
            tarjan(u);
            low[v] = min(low[v] , low[u]);
        }
        if(instack[u]){
            low[v] = min(low[v] , dfn[u]);
        }
    }
    if(dfn[v] == low[v]){
        ++tot;
        while(!S.empty()){
            int b = S.back();
            comp[tot].push_back(b);
            compID[b] = tot;
            S.pop_back();
            instack[b] = false;
            if(b == v)break;
        }
    }
}
 
void DFS(int v){
    int delta = 0;
    for(int u : G[v]){
        if(u != v){
            DFS(u);
            delta = max(delta , compval[u]);
        }
    }
    compval[v] += delta;
}
 
int main(){
    int i , j;
    scanf("%d %d %d" , &N , &M , &D);
    for(i = 1; i <= M; ++i){
        int u , v;
        scanf("%d %d" , &u , &v);
        --u; --v;
        for(j = 0; j < D; ++j){
            g[ID(u , j)].push_back(ID(v , (j + 1) % D));
        }
    }
    for(i = 0; i < N; ++i){
        scanf("%s" , open[i]);
        for(j = 0; j < D; ++j){
            dfn[ID(i , j)] = -1;
            low[ID(i , j)] = INF;
        }
    }
    for(i = 0; i < N; ++i){
        for(j = 0; j < D; ++j){
            if(~dfn[ID(i , j)])continue;
            tarjan(ID(i , j));
        }
    }
    for(i = 1; i <= tot; ++i){
        //set<int> vis;
        map<int , int> vis;
        for(int u : comp[i]){
            for(int v : g[u]){
                //vis.insert(compID[v]);
                vis[compID[v]] = 1;
            }
        }
        //for(int u : vis){
        //    G[i].push_back(u);
        //}
        for(auto& e : vis){
            G[i].push_back(e.first);
        }
    }
    for(i = 1; i <= tot; ++i){
        //set<int> vis;
        map<int , int> vis; 
        for(int u : comp[i]){
            int v = u % N , d = u / N;
            if(open[v][d] == '0')continue;
            //if(vis.find(v) == vis.end()){
            if(!vis[v]){
               //vis.insert(v);
                vis[v] = 1;
                ++compval[i];
            }
        }
    }
    DFS(compID[ID(0 , 0)]);
    printf("%d\n" , compval[compID[ID(0 , 0)]]);
}