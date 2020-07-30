#pragma GCC optimize(3)
#pragma GCC optimize(2)
#include <bits/stdc++.h>
#define x first
#define y second
#define ID if(false)
using namespace std;
typedef pair<int , int> ii;

const int maxn = 5e5 + 10;
vector<ii> qs[maxn];
vector<int> g[maxn];
vector<int> *vec[maxn];
int cnt[maxn][26];
char val[maxn];
int sz[maxn];
int depth[maxn];
int ans[maxn];
int N , Q;

void getsz(int v , int p , int d){
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
        vec[v] = new vector<int>();
    }
    vec[v]->push_back(v);
    ++cnt[depth[v]][val[v] - 'a'];
    for(int u : g[v]){
        if(u != p && u != bigChild){
            for(int x : *vec[u]){
                vec[v]->push_back(x);
                ++cnt[depth[x]][val[x] - 'a'];
            }
        }
    }
    // answer query related to v
    ID{
        printf("now at tree rooted at %d\n" , v);
        for(auto& q : qs[v]){
            printf("q : %d\n" , q.x);
        }
        for(int d = 1; d <= N; ++d){
            for(int j = 0; j < 26; ++j){
                if(cnt[d][j])printf("cnt[%d][%d] = %d\n" , d , j , cnt[d][j]);
            }
        }
        printf("\n");
    }
    for(auto& q : qs[v]){
        int d = q.x , id = q.y;
        int nodd = 0;
        for(int i = 0; i < 26; ++i)if(cnt[d][i] % 2)++nodd;
        if(nodd <= 1) ans[id] = 1;
        else ans[id] = 0;
    }
    if(keep == 0){
        for(int u : *vec[v]){
            --cnt[depth[u]][val[u] - 'a'];
        }
    }
}

int main(){
    scanf("%d %d" , &N , &Q);
    for(int i = 2; i <= N; ++i){
        int p; scanf("%d" , &p);
        g[i].push_back(p);
        g[p].push_back(i);
    }
    scanf("%s" , val + 1);
    for(int i = 1; i <= Q; ++i){
        int v , h; scanf("%d %d" , &v , &h);
        qs[v].emplace_back(h , i);
    }
    getsz(1 , 1 , 1);
    DFS(1 , 1 , 1);
    for(int i = 1; i <= Q; ++i)printf("%s\n" , ans[i] ? "Yes" : "No");
}       