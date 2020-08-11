/*
    TLE
*/
#include <bits/stdc++.h>
#define ID if(0)
using namespace std;
typedef long long ll;
const int maxn = 50000 + 10;
vector<int> g[maxn];
int sz[maxn];
int max_size[maxn];
ll cnt[maxn];
bool dead[maxn];
int N , K , centroid;
ll ans = 0 , delta = 0;

void get_centroid(int v , int fa , int total){
    sz[v] = 1;
    max_size[v] = 0;
    for(int u : g[v]){
        if(!dead[u] && u != fa){
            get_centroid(u , v , total);
            sz[v] += sz[u];
            max_size[v] = max(max_size[v] , sz[u]);
        }
    }
    max_size[v] = max(max_size[v] , total - sz[v]); // fa
    if(max_size[centroid] > max_size[v])centroid = v;
}

void DFS(int v , int fa , int dis , int f){
    if(f)++cnt[dis];
    else --cnt[dis];
    for(int u : g[v]){
        if(!dead[u] && u != fa){
            DFS(u , v , dis + 1 , f);
        }
    }
}

void cal(int v , int fa , int dis){
    if(dis > K)return;
    delta += cnt[K - dis];
    for(int u : g[v]){
        if(!dead[u] && u != fa){
            cal(u , v , dis + 1);
        }
    }
}

void solve(int v){
    ID printf("centroid = %d\n" , centroid);
    DFS(v , v , 0 , 1);
    delta = 0;
    delta += cnt[K];
    for(int u : g[v]){
        if(!dead[u]){
            DFS(u , v , 1 , 0);
            cal(u , v , 1);
            DFS(u , v , 1 , 1);
        }
    }
    DFS(v , v , 0 , 0);
    ans += delta / 2;
    dead[v] = 1;
    for(int u : g[v]){
        if(!dead[u]){
            centroid = 0;
            max_size[0] = sz[u];
            get_centroid(u , 0 , sz[u]);
            solve(u);
        }
    }
    
}

int main(){
    scanf("%d %d" , &N , &K);
    for(int i = 1; i < N; ++i){
        int x , y; 
        scanf("%d %d" , &x , &y);
        g[x].push_back(y);
        g[y].push_back(x);
    }
    max_size[0] = N;
    centroid = 0;
    get_centroid(1 , 0 , N);
    solve(centroid);
    printf("%lld\n" , ans);
}   