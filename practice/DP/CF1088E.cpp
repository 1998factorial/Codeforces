#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int maxn = 3e5 + 10;
const int INF = 1e9 + 10;
const ll INF64 = 1e18;
int N , a[maxn] , cnt = 0;
vector<int> g[maxn]; 
ll DP[maxn] , mx;

void DFS(int v , int p){
    DP[v] = a[v];
    for(int u : g[v]){
        if(u == p)continue;
        DFS(u , v);
        if(DP[u] >= 0){
            DP[v] += DP[u];
        }
    }
    //printf("DP[%d] = %lld\n" , v , DP[v]);
}

void DFS2(int v , int p){
    DP[v] = a[v];
    for(int u : g[v]){
        if(u == p)continue;
        DFS2(u , v);
        if(DP[u] >= 0){
            DP[v] += DP[u];
        }
    }
    if(DP[v] == mx){
        ++cnt;
        DP[v] = 0;
    }
}

int main(){
    scanf("%d" , &N);
    mx = -INF;
    for(int i = 1; i <= N; ++i)scanf("%d" , &a[i]) , mx = max(mx , (ll)a[i]);
    for(int i = 1; i < N; ++i){
        int u , v;
        scanf("%d %d" , &u , &v);
        g[u].push_back(v);
        g[v].push_back(u);
    }
    if(mx <= 0){
        ll ret = 0 , cnt = 0;
        for(int v = 1; v <= N; ++v){
            if(a[v] == mx)ret += a[v] , ++cnt;
        }
        printf("%lld %lld\n" , ret , cnt);
    }
    else{
        DFS(1 , 1);
        mx = -INF64;
        for(int v = 1; v <= N; ++v){
            mx = max(mx , DP[v]);
        }
        DFS2(1 , 1);
        printf("%lld %d\n" , mx * cnt , cnt);
    }
}


