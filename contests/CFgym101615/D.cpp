#include <bits/stdc++.h>
using namespace std;
const int maxn = 50005;
vector<array<int , 2>> g[maxn];
int N , dfn[maxn] , R[maxn] , cnt = 0 , bad[maxn] , fa[maxn] , sum[maxn];
// find all bad points
// if vertex v has (x , c) (y , c) having same colour
// subtree rooted at x and y will be marked as bad
// this can be done by range covering
// be careful with parent case
void DFS(int v , int p){
    dfn[v] = ++cnt;
    fa[v] = p;
    for(auto& e : g[v]){
        if(e[0] == p)continue;
        DFS(e[0] , v);
    }
    R[v] = cnt;
}

int main(){
    scanf("%d" , &N);
    for(int i = 1; i < N; ++i){
        int u , v , c;
        scanf("%d %d %d" , &u , &v , &c);
        g[u].push_back({v , c});
        g[v].push_back({u , c});
    }
    DFS(1 , 0);
    for(int v = 1; v <= N; ++v){
        vector<array<int , 2>> edges;
        for(auto& e : g[v]){
            edges.push_back({e[1] , e[0]});
        }
        if(edges.empty())continue;
        sort(edges.begin() , edges.end());
        int j = 0 , k = 0;
        for(; j < edges.size(); j = k){
            for(k = j; k < edges.size() && edges[k][0] == edges[j][0]; ++k);
            if(k - j >= 2){
                for(int x = j; x < k; ++x){
                    int u = edges[x][1];
                    if(u == fa[v]){
                        ++sum[1];
                        --sum[dfn[v]];
                        ++sum[R[v] + 1];
                    }
                    else{
                        ++sum[dfn[u]];
                        --sum[R[u] + 1];
                    }
                }
            }
        }
    }
    for(int i = 1; i <= N; ++i)sum[i] += sum[i - 1];
    int sz = 0;
    for(int i = 1; i <= N; ++i){
        if(!sum[dfn[i]])++sz;
    }
    printf("%d\n" , sz);
    for(int i = 1; i <= N; ++i){
        if(!sum[dfn[i]]){
            printf("%d\n" , i);
        }
    }
}