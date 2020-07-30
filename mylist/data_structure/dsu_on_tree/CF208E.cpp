#pragma GCC optimize(3)
#pragma GCC optimize(2)
#include <bits/stdc++.h>
#define ID if(0)
#define x first
#define y second
#define mk make_pair
using namespace std;
typedef pair<int , int> ii;

const int maxn = 1e5 + 10;
vector<int> g[maxn];
vector<int> *vec[maxn];
vector<ii> qs[maxn];
int depth[maxn];
int cnt[maxn];
int ans[maxn];
int sz[maxn];
int up[maxn][25];
int N , Q , L;
bool root[maxn];


void getsz(int v , int p , int d){
    up[v][0] = p;
    sz[v] = 1;
    depth[v] = d;
    for(int u : g[v]){
        if(u != p){
            getsz(u , v , d + 1);
            sz[v] += sz[u];
        }
    }
    ID{
        printf("sz[%d] = %d\n" , v , sz[v]);
        printf("depth[%d] = %d\n" , v , depth[v]);
    }
}

void add(int v , int x){
    vec[v]->push_back(x);
    ++cnt[depth[x]];
}

void DFS(int v , int p , bool keep){
    int mx = -1 , bigChild = -1;
    for(int u : g[v]){
        if(u != p && mx < sz[u]){
            mx = sz[u];
            bigChild = u;
        }
    }
    for(int u : g[v]){
        if(u != p && u != bigChild){
            DFS(u , v , 0);
        }
    }
    if(bigChild != -1){
        DFS(bigChild , v , 1);
        vec[v] = vec[bigChild];
    }
    else{
        vec[v] = new vector<int> ();
    }
    add(v , v);
    for(int u : g[v]){
        if(u != p && u != bigChild){
            for(int x : *vec[u]){
                add(v , x);
            }
        }
    }
    
    // answer query
    for(auto& e : qs[v]){
        ans[e.y] = cnt[e.x] - 1;
    }


    ID{
        printf("at tree rooted at %d\n" , v);
        for(int i = 0; i <= N; ++i){
            printf("cnt[%d] = %d\n" , i , cnt[i]);
        }
        printf("\n");
    }

    if(keep == 0){
        for(int i : *vec[v]){
            --cnt[depth[i]];
        }
    }
}

int main(){
    scanf("%d" , &N);
    for(int i = 1; i <= N; ++i){
        int x; scanf("%d" , &x);
        if(x == 0){
            root[i] = 1;
        }
        else{
            g[i].push_back(x);
            g[x].push_back(i);
        }
    }
    for(int i = 1; i <= N; ++i){
        if(root[i]){
            getsz(i , i , 1);
        }
    }
    L = ceil(log2(N));
    for(int j = 1; j <= L; ++j){
        for(int i = 1; i <= N; ++i){
            up[i][j] = up[up[i][j - 1]][j - 1];
        }
    }
    ID{
        for(int j = 0; j <= L; ++j){
            for(int i = 1; i <= N; ++i){
                printf("up[%d][%d] = %d\n" , i , j , up[i][j]);
            }
        }
    }
    scanf("%d" , &Q);
    for(int q = 1; q <= Q; ++q){
        int v , h; scanf("%d %d" , &v , &h);
        // do something about the query
        if(depth[v] < h + 1)continue;
        int vv = v;
        for(int i = L; i >= 0; --i){
            if((1 << i) <= h){
                v = up[v][i];
                h -= (1 << i);
            }
        }
        ID printf("ask (%d %d) at %d\n" , vv , q , v);
        qs[v].emplace_back(depth[vv] , q);
    }
    for(int i = 1; i <= N; ++i){
        if(root[i]){
            DFS(i , i , 0);
        }
    }
    for(int i = 1; i <= Q; ++i){
        printf("%d " , ans[i]);
    }
    printf("\n");
}   