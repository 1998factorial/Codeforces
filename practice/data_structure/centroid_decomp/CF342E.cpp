/*
    Centroid tree , rating 2400
    build centroid tree first.
    for painting v , we need to go up to v's ancestor (on centroid tree) , update their ans by
    ans[v] = 0
    ans[p] = min(ans[p] , ans[v] + dist(v , p)) , dist can be done using dis(v) + dis(p) - 2 * dis(lca(v , p))
    for query on v , we also need to go up on centroid tree.
    ret = min(ret , ans[p] + dist(v , p))

    why does it work?
    ans[v] = minimal distance from v to any red vertex in the part where v is the centroid
    as we go up from v on the centroid tree , answer = min(ans[p] + dist(p -> v))
    this will include every part of the old tree that contains v , thus the answer of v

    centroid has at most O(logN) levels , for each level we can compute the answer in 
    O(logN) using binary flip , so the time complexity is O(NlogN + Q * logN * logN)
    in which 5s is enough
*/
#include <bits/stdc++.h>
#define x first
#define y second
#define mk make_pair
#define ID if(0)
#define ii pair<int , int>
#define ll long long
using namespace std;

const int maxn = 1e5 + 10;
const int INF = 1e9;
int N , Q , L;
vector<int> g[maxn]; // old graph
vector<int> ct[maxn]; // centroid tree
bool dead[maxn]; // dead node
int tin[maxn]; // in time
int tout[maxn]; // out time
int up[maxn][25]; // binary fliping 
int depth[maxn]; // depth of node in old tree
int ans[maxn]; // shortest distance to any red vertex
int sz[maxn]; // subtree size
int cp[maxn]; // parent on centroid tree
int p[maxn]; // parent
int root = 0; // centorid of the tree
int tot = 0;

void getsz(int v , int fa , int d){
    tin[v] = ++tot;
    sz[v] = 1;
    depth[v] = d;
    p[v] = up[v][0] = fa;
    for(int u : g[v]){
        if(u != p[v]){
            getsz(u , v , d + 1);
            sz[v] += sz[u];
        }
    }
    tout[v] = tot;
    ID{
        printf("p[%d] = %d\n" , v , p[v]);
        printf("depth[%d] = %d\n" , v , depth[v]);
        printf("sz[%d] = %d\n" , v , sz[v]);
    }
}

int decompose(int vv , int total , int fa){ // this part decompose the old graph into a centroid tree
    int v = vv;
    for(;;){
        int nv = -1;
        for(int u : g[v]){
            if(dead[u] || u == p[v])continue;
            if(sz[u] > total / 2)nv = u; // centroid must be in the larger part
        }   
        if(total - sz[v] > total / 2 && p[v] != -1 && !dead[p[v]])nv = p[v];
        if(nv != -1)v = nv;
        else break; // centroid found which is v
    }
    for(int u = p[v]; u != p[u] && !dead[u]; u = p[u]){
        sz[u] -= sz[v];
    }
    dead[v] = 1;
    for(int u : g[v]){
        if(!dead[u]){
            int sizet = sz[u];
            if(u == p[v])sizet = total - sz[u];
            int nv = decompose(u , sizet , v);
            ct[v].push_back(nv);
            cp[nv] = v;
        }
    }
    return v;
}

bool is_ancestor(int u , int v){ // u is v's ancestor ?
    return tin[u] <= tin[v] && tout[u] >= tout[v]; 
}

int lca(int u , int v){
    if(is_ancestor(u , v))return u;
    if(is_ancestor(v , u))return v;
    for(int i = L; i >= 0; --i){
        if(!is_ancestor(up[u][i] , v))
            u = up[u][i];
    }
    return up[u][0];
}

int getDist(int v , int u){
    return depth[v] + depth[u] - 2 * depth[lca(v , u)];
}

void show_centroid_tree(int v){
    for(int u : ct[v]){
        printf("%d -- %d\n" , v , u);
        show_centroid_tree(u);
    }
}

void update(int v){ // paint vertex v to red
    ID printf("paint %d to red\n" , v);
    ans[v] = min(ans[v] , 0);
    for(int u = cp[v]; u != -1; u = cp[u]){ 
        ans[u] = min(ans[u] , getDist(u , v) + ans[v]);
        ID printf("ans[%d] = %d\n" , u , ans[u]);
    }
}

int query(int v){ // query answer on v
    ID printf("what is the min dist from %d to any red vertex?\n" , v);
    int ret = ans[v];
    ID printf("current ans = %d\n" , ret);
    for(int u = cp[v]; u != -1; u = cp[u]){
        ret = min(ret , getDist(u , v) + ans[u]);
        ID printf("checking %d which is %d\n" , u , getDist(u , v) + ans[u]);
    }
    ID printf("ans = %d\n" , ret);
    return ret;
}

int main(){
    scanf("%d %d" , &N , &Q);
    L = ceil(log2(N));
    for(int i = 1; i < N; ++i){
        int x , y; scanf("%d %d" , &x , &y);
        g[x].push_back(y);
        g[y].push_back(x);
    }
    for(int i = 1; i <= N; ++i)p[i] = -1 , ans[i] = INF , cp[i] = -1;
    getsz(1 , 1 , 1);
    for(int j = 1; j <= L; ++j){
        for(int i = 1; i <= N; ++i){
            up[i][j] = up[up[i][j - 1]][j - 1];
        }
    }
    root = decompose(1 , N , -1);
    ID printf("centroid = %d\n" , root);
    ID show_centroid_tree(root);
    update(1); // update all 1's ancestors on centroid tree 
    for(int q = 1; q <= Q; ++q){
        int t , v; scanf("%d %d" , &t , &v);
        if(t == 1){
            // paint v to red
            update(v);
        }
        else if(t == 2){
            // query min dist to v (from any red)
            printf("%d\n" , query(v));
        }
    }
}