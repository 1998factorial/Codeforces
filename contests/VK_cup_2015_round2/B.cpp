#include <bits/stdc++.h>
#define x first
#define y second
#define ID if(1)
using namespace std;
typedef long long ll;
typedef pair<ll , ll> ii;
const ll INF = 1e18;
const int maxn = 2e5 + 10;
ll a[maxn] , DP[maxn][2];
vector<int> g[maxn];
int N;

void DFS(int v , int p){
    DP[v][1] = a[v];
    DP[v][0] = -INF;
    vector<ii> vis;
    for(int u : g[v]){
        if(u != p){
            DFS(u , v);
            vis.emplace_back(DP[u][0] , DP[u][1]);
        }
    }
    if(g[v].size() > 1){
        int sz = vis.size();
        vector<vector<ll>> DP2(sz, vector<ll> (2 , -INF));
        DP2[0][0] = vis[0].x; DP2[0][1] = vis[0].y;
        for(int i = 1; i < sz; ++i){
            ll even = vis[i].x , odd = vis[i].y;
            DP2[i][0] = max(DP2[i][0] , DP2[i - 1][0]);
            DP2[i][1] = max(DP2[i][1] , DP2[i - 1][1]);
            DP2[i][1] = max(DP2[i][1] , DP2[i - 1][0] + odd);
            DP2[i][0] = max(DP2[i][0] , DP2[i - 1][1] + odd);
            DP2[i][0] = max(DP2[i][0] , DP2[i - 1][0] + even);
            DP2[i][1] = max(DP2[i][1] , DP2[i - 1][1] + even);
        }    
        printf("at vertex %d\n" , v);
        ID {
            for(auto& e : vis){
                printf("%lld %lld\n" , e.x , e.y);
            }
        }
        for(int i = 0; i < sz; ++i){
            for(int j = 0; j < 2; ++j){
                printf("DP2[%d][%d] = %lld\n" , i , j , DP2[i][j]);
            }
        }
        DP[v][0] = max(DP2[sz - 1][0] , DP[v][0]);
        DP[v][0] = max(DP2[sz - 1][1] + a[v] , DP[v][0]);
        DP[v][1] = max(DP2[sz - 1][1] , DP[v][1]);
        DP[v][1] = max(DP2[sz - 1][0] + a[v] , DP[v][1]);
    }
    ID {
        printf("DP[%d][%d] = %lld\n" , v , 0 , DP[v][0]);
        printf("DP[%d][%d] = %lld\n" , v , 1 , DP[v][1]);
    }
}

int main(){
    scanf("%d" , &N);
    for(int i = 1; i <= N; ++i){
        //for(int j : {0 , 1})DP[i][j] = -INF;
        int p; scanf("%d %lld" , &p , &a[i]);
        if(~p){
            g[p].push_back(i);
            g[i].push_back(p);
        }
    }
    DFS(1 , 0);
    printf("%lld\n" , DP[1][1]);
}