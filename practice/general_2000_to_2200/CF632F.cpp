#include <bits/stdc++.h>
using namespace std;
// a[i][j] <= max(a[i][k] , a[k][j]) <= max(a[i][x] , a[x][k] , a[k][j])
// so a[i][j] <= the max edge in simple path start at i end at j for all simple path
// so a[i][j] <= minimal max edge in any simple path start at i end at j
// MST minimses the max edge on path i to j, for all i and j
// so a matrix is magic if for all a[i][j], it can be in MST
int N , L;
int a[2505][2505] , up[2505][20] , DP[2505][20] , tin[2505] , tout[2505] , timmer = 0;
vector<array<int , 2>> mst[2505];
int fa[2505];

int find(int x){
    return x == fa[x] ? x : fa[x] = find(fa[x]);
}

void merge(int x , int y){
    x = find(x); 
    y = find(y);
    fa[x] = y;
}

void DFS(int v , int p , int cost){
    tin[v] = ++timmer;
    up[v][0] = p;
    DP[v][0] = cost;
    for(int i = 1; i <= L; ++i){
        up[v][i] = up[up[v][i - 1]][i - 1];
        DP[v][i] = max(DP[v][i - 1] , DP[up[v][i - 1]][i - 1]);
    }
    for(auto& e : mst[v]){
        int nv = e[0] , w = e[1];
        if(nv == p)continue;
        DFS(nv , v , w);
    }
    tout[v] = ++timmer;
}

bool isAncestor(int u , int v){ // check if u is ancestor of v
    return tin[u] <= tin[v] && tout[u] >= tout[v];
}

int getmax(int v , int u){
    int ans = 0;
    if(tin[v] >= tin[u])swap(u , v);
    if(isAncestor(v , u)){
        for(int i = L; i >= 0; --i){
            if(!isAncestor(up[u][i] , v)){
                ans = max(ans , DP[u][i]);
                u = up[u][i];
            }
        }
        ans = max(ans , DP[u][0]);
    }
    else{
        int x = u , y = v;
        // move up u first
        for(int i = L; i >= 0; --i){
            if(!isAncestor(up[x][i] , v)){
                ans = max(ans , DP[x][i]);
                x = up[x][i];
            }
        }
        ans = max(ans , DP[x][0]);
        // move up v then
        for(int i = L; i >= 0; --i){
            if(!isAncestor(up[y][i] , u)){
                ans = max(ans , DP[y][i]);
                y = up[y][i];
            }
        }
        ans = max(ans , DP[y][0]);
    }
    return ans;
}

int main(){
    scanf("%d" , &N);
    for(int i = 1; i <= N; ++i){
        for(int j = 1; j <= N; ++j){
            scanf("%d" , &a[i][j]);
        }
    }
    int ok = 1;
    for(int i = 1; i <= N; ++i)if(a[i][i] != 0)ok = 0;
    for(int i = 1; i <= N; ++i){ 
        for(int j = 1; j <= N; ++j){
            if(a[i][j] != a[j][i])ok = 0;
        }
    }
    if(!ok){
        printf("NOT MAGIC\n");
        return 0;
    }
    // get MST
    vector<array<int , 3>> edges;
    for(int i = 1; i <= N; ++i){
        for(int j = i + 1; j <= N; ++j){
            edges.push_back({a[i][j] , i , j});
        }
    }
    sort(edges.begin() , edges.end());
    for(int i = 1; i <= N; ++i)fa[i] = i;
    for(auto& e : edges){
        int x = e[1] , y = e[2];
        if(find(x) != find(y)){
            mst[x].push_back({y , e[0]});
            mst[y].push_back({x , e[0]});
            merge(x , y);
        }
    }
    // now we need to check for all a[i][j] , i < j
    // a[i][j] <= max edge on path(i , j)
    // we use binary lifting here
    L = ceil(log2(N));
    DFS(1 , 1 , 0);
    for(int i = 1; i <= N; ++i){
        for(int j = i + 1; j <= N; ++j){
            if(a[i][j] > getmax(i , j)){
                printf("NOT MAGIC\n");
                return 0;
            }
        }
    }
    printf("MAGIC\n");
}