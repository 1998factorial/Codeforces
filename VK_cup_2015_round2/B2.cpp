#include <bits/stdc++.h>
#define x first
#define y second
#define ID if(0)
using namespace std;
typedef long long ll;
typedef pair<ll , ll> ii;
const ll INF = 1e18;
const int maxn = 2e5 + 10;
ll a[maxn] , DP[maxn][2][2];
vector<int> g[maxn];
int N;
bool vis[maxn];
void DFS(int v){
    DP[v][1][0] = -INF;
    DP[v][1][1] = a[v];
    DP[v][0][0] = 0;
    DP[v][0][1] = -INF;
    if(g[v].size() <= 0){
        return;
    }
    vector<vector<ll>> vec;
    for(int u : g[v]){
        DFS(u);
        vec.push_back({DP[u][1][1] , DP[u][0][0] , DP[u][0][1]});
    }
    int sz = vec.size();
    vector<vector<ll>> cost(sz , vector<ll> (2 , -INF));
    cost[0][0] = vec[0][1]; cost[0][1] = max(vec[0][0] , vec[0][2]);
    for(int i = 1; i < sz; ++i){
        for(int j = 0; j < 2; ++j)cost[i][j] = max(cost[i][j] , cost[i - 1][j]);
        cost[i][0] = max(cost[i][0] , cost[i - 1][0] + vec[i][1]);
        cost[i][0] = max(cost[i][0] , cost[i - 1][1] + max(vec[i][0] , vec[i][2]));
        cost[i][1] = max(cost[i][1] , cost[i - 1][1] + vec[i][1]);
        cost[i][1] = max(cost[i][1] , cost[i - 1][0] + max(vec[i][0] , vec[i][2]));
    }
    DP[v][1][1] = max(DP[v][1][1] , cost[sz - 1][0] + a[v]);
    DP[v][0][0] = max(DP[v][0][0] , cost[sz - 1][0]);
    DP[v][0][1] = max(DP[v][0][1] , cost[sz - 1][1]);
    ID {
        for(int i : {0 , 1}){
            for(int j : {0 , 1}){
                printf("DP[%d][%d][%d] = %lld\n" , v , i , j , DP[v][i][j]);
            }
        }
    }
}

int main(){
    scanf("%d" , &N);
    for(int i = 1; i <= N; ++i){
        int p; scanf("%d %lld" , &p , &a[i]);
        if(~p){
            g[p].push_back(i);
        }
    }
    DFS(1);
    printf("%lld\n" , max(DP[1][1][1] , max(DP[1][0][1] , DP[1][0][0])));
}