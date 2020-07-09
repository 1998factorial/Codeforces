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
    int u , v , w , id , p1 , p2;
    edge(){}
    edge(int a , int b , int c , int d , int e , int f) : u(a) , v(b) , w(c) , id(d) , p1(e) , p2(e) {}
    bool operator < (const edge& rhs) const {
        return w < rhs.w;
    }
};
vector<ii> g[maxn];
vector<edge> edges;
int dfn[maxn] , low[maxn] , fa[maxn] , ans[maxn];
bool bridge[maxn];
int N , M , tot;

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
    for(int i = 1; i <= M; ++i){
        int x , y , z; scanf("%d %d %d" , &x , &y , &z);
        edges.emplace_back(x , y , z , i , 0 , 0);
    }
    sort(edges.begin() , edges.end());
    for(int i = 1; i <= N; ++i)fa[i] = i;
    for(int i = 0 , j = 0; i < M; i = j + 1){
        tot = 0;
        while(j + 1 < M && edges[j + 1].w == edges[i].w)++j; // group by same weights
        for(int x = i; x <= j; ++x){
            edges[x].p1 = find(edges[x].u);
            edges[x].p2 = find(edges[x].v);
            if(edges[x].p1 == edges[x].p2)ans[edges[x].id] = 3; // creates cycle , not in any MST
        }
        for(int x = i; x <= j; ++x){
            int a = edges[x].p1 , b = edges[x].p2;
            if(a != b){
                dfn[a] = dfn[b] = 0;
                g[a].clear();
                g[b].clear();
            }
        }
        for(int x = i; x <= j; ++x){
            int a = edges[x].p1 , b = edges[x].p2;
            if(a != b){
                g[a].emplace_back(b , edges[x].id); // we can get from CC a to CC b using the id-th edge
                g[b].emplace_back(a , edges[x].id); // we can get from CC b to CC a using the id-th edge
            }
        }
        for(int x = i; x <= j; ++x){
            int a = edges[x].p1 , b = edges[x].p2;
            if(a != b){
                if(dfn[a] == 0)tarjan(a , 0);
                if(dfn[b] == 0)tarjan(b , 0);
            }
        }
        for(int x = i; x <= j; ++x){
            int a = edges[x].p1 , b = edges[x].p2;
            if(a != b){
                if(bridge[edges[x].id])ans[edges[x].id] = 1;
                else ans[edges[x].id] = 2;
            }
            a = find(edges[x].u);
            b = find(edges[x].v);
            if(a != b){
                fa[a] = b;
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
