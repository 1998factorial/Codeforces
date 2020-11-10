/*
    MST , rating 2300
    consider the process of Kruskal , when adding edges into spanning tree ,
    we consider all edges with same weight. each of these edges will connect either
    connect 2 CC or create a cycle , the one that creates cycle will not be in any MST ,
    the one that connects 2 CC will either be in all MST or at least one MST.
    if we consider for each CC as vertice on graph , for this graph G' , an edge can not
    be ignored if it is a bridge , in another word , it will make the number of CC be larger
    if we do not include it into MST. This can be done by tarjan.
*/
#include <bits/stdc++.h>
using namespace std;
typedef pair<int , int> ii;

const int maxn = 1e5 + 10;
struct edge{
    int u , v , id , p1 , p2;
    edge(){}
    edge(int a , int b , int c , int d , int e) : u(a) , v(b) , id(c) , p1(d) , p2(e) {}
};
vector<edge> edges[maxn * 10];
vector<ii> g[maxn];
int fa[maxn];
int dfn[maxn] , low[maxn];
int ans[maxn];
int N , M;
bool bridge[maxn];
int tot;

int find(int x){
    return fa[x] == x ? x : fa[x] = find(fa[x]);
}

void tarjan(int v , int id){
    dfn[v] = low[v] = ++tot;
    for(auto& e : g[v]){
        if(e.second == id)continue;
        if(dfn[e.first] == 0){
            tarjan(e.first , e.second);
            low[v] = min(low[v] , low[e.first]);
            if(dfn[v] < low[e.first])bridge[e.second] = 1;
        }
        else{
            low[v] = min(low[v] , dfn[e.first]);
        }
    }
}

int main(){
    scanf("%d %d" , &N , &M);
    for(int i = 1; i <= N; ++i)fa[i] = i;
    for(int i = 1; i <= M; ++i){
        int u , v , w;
        scanf("%d %d %d" , &u , &v , &w);
        edges[w].emplace_back(u , v , i , 0 , 0);
    }
    for(int i = 0; i <= 1000000; ++i){
        if(edges[i].empty())continue;
        tot = 0;
        for(auto& e : edges[i]){
            e.p1 = find(e.u);
            e.p2 = find(e.v);
            if(e.p1 > e.p2)swap(e.p1 , e.p2);
        }
        for(auto& e : edges[i]){
            if(e.p1 == e.p2){
                ans[e.id] = 3; // not in any tree
            }
            else{
                g[e.p1].clear();
                g[e.p2].clear();
                dfn[e.p1] = dfn[e.p2] = 0;
            }
        }
        for(auto& e : edges[i]){
            if(e.p1 != e.p2){
                g[e.p1].emplace_back(e.p2 , e.id);
                g[e.p2].emplace_back(e.p1 , e.id);
            }
        }
        for(auto& e : edges[i]){
            if(e.p1 != e.p2){
                if(dfn[e.p1] == 0)tarjan(e.p1 , 0);
                if(dfn[e.p2] == 0)tarjan(e.p2 , 0);
            }
        }
        for(auto& e : edges[i]){
            if(e.p1 != e.p2){
                if(bridge[e.id])ans[e.id] = 1;
                else ans[e.id] = 2;
            }

        }
        for(auto& e : edges[i]){
            int x = find(e.u);
            int y = find(e.v);
            if(x != y){
                fa[x] = y;
            }
        }
    }
    for(int i = 1; i <= M; ++i){
        if(ans[i] == 1){
            printf("any\n");
        }
        if(ans[i] == 2){
            printf("at least one\n");
        }
        if(ans[i] == 3){
            printf("none\n");
        }
    }
}
