#include <bits/stdc++.h>
using namespace std;

struct edge{
    int u , v , p;
    edge(){}
    edge(int u_ , int v_ , int p_) : u(u_) , v(v_) , p(p_) {}
    bool operator < (const edge& rhs) const {
        return p > rhs.p;
    }
};

const int maxn = 3e5 + 10;
int N , M , Q , qs[maxn];
array<int , 2> ans[maxn];
vector<edge> edges;
int fa[maxn] , deg[maxn] , ndeg2[maxn] , sz[maxn];
int ne = 0 , nv = 0 , ncycle = 0 , deg2 = 0;
int find(int x){
    return fa[x] == x ? x : fa[x] = find(fa[x]);
}
int main(){
    scanf("%d %d" , &N , &M);
    for(int i = 1; i <= N; ++i)fa[i] = i , sz[i] = 1;
    for(int i = 1; i <= M; ++i){
        int u , v , p;
        scanf("%d %d %d" , &u , &v , &p);
        edges.emplace_back(u , v , p);
    }
    scanf("%d" , &Q);
    vector<int> ids;
    for(int i = 1; i <= Q; ++i){
        scanf("%d" , &qs[i]);
        ids.push_back(i);
    }
    sort(ids.begin() , ids.end() , [&](int l , int r){
        return qs[l] > qs[r];
    });
    sort(edges.begin() , edges.end());
    int j = 0;
    for(int i : ids){
        int v = qs[i];
        int k = j;
        while(j < M && edges[j].p >= v)++j;
        for(; k < j; ++k){
            ++ne;
            int u = edges[k].u , v = edges[k].v;
            int x = find(u) , y = find(v);
            if(!deg[u])++nv;
            if(!deg[v])++nv;
            if(deg[u] == 2){
                if(sz[x] == ndeg2[x])--ncycle;
                --deg2 , --ndeg2[x];
            }
            if(deg[v] == 2){
                if(sz[y] == ndeg2[y])--ncycle;
                --deg2 , --ndeg2[y];
            }
            ++deg[u];
            ++deg[v];
            if(deg[u] == 2){
                if(sz[x] == ndeg2[x])++ncycle;
                ++deg2 , ++ndeg2[x];
            }
            if(deg[v] == 2){
                if(sz[y] == ndeg2[y])++ncycle;
                ++deg2 , ++ndeg2[y];
            }
            if(x != y){
                fa[x] = y;
                sz[y] += sz[x];
                ndeg2[y] += ndeg2[x];
            }
            if(sz[y] == ndeg2[y])++ncycle;
        }
        // answer this query 
        ans[i] = {nv + ncycle - deg2 , ne - deg2 + ncycle};
    }
    for(int i = 1; i <= Q; ++i){
        printf("%d %d\n" , ans[i][0] , ans[i][1]);
    }
}