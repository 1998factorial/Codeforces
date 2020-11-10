#include <bits/stdc++.h>
#define x first
#define y second
#define ID if(0)
using namespace std;
typedef long long ll;
typedef pair<int , int> ii;
const ll INF = 1e18;
int N , M , s , cnt[55];
ll DP[55][55][55][55]; // O(N * N * M * M)
vector<ii> g[55];

int DFS(int v , int p){
    int ret = cnt[v];
    for(auto& e : g[v]){
        if(e.x != p){
            ret += DFS(e.x , v);
        }
    }
    return ret;
}

ll solve(int v , int u , int fc , int bc){
    if(!fc && !bc)return 0; // done
    ll& ret = DP[v][u][fc][bc];
    if(~ret)return ret; // computed
    int sz = g[u].size();
    if(sz == 1){
        if(!bc)return 0; // done
        return solve(u , v , bc , 0) + g[u][0].y; // turn back from leave
    }
    vector<ll> cost(fc + 1);
    cost[0] = INF;
    for(int i = 0; i < sz; ++i){
        if(g[u][i].x != v){
            for(int j = fc; j >= 1; --j){
                for(int k = j; k >= 1; --k){
                    cost[j] = max(cost[j] , min(cost[j - k] , solve(u , g[u][i].x , k , fc + bc - k) + g[u][i].y));
                }
            }
        }
    }
    ret = cost[fc];
    ID printf("DP[%d][%d][%d][%d] = %lld\n" , v , u , fc , bc , ret);
    return ret;
}

int main(){
    scanf("%d" , &N);
    for(int i = 1; i <= N - 1; ++i){
        int x , y , w;
        scanf("%d %d %d" , &x , &y , &w);
        g[x].emplace_back(y , w);
        g[y].emplace_back(x , w);
    }
    scanf("%d %d" , &s , &M);
    for(int i = 1; i <= M; ++i){
        int x;
        scanf("%d" , &x);
        ++cnt[x];
    }
    memset(DP , -1 , sizeof(DP));
    ll ans = INF;
    for(auto& e : g[s]){
        int nc = DFS(e.x , s);
        ans = min(ans , solve(s , e.x , nc , M - nc) + e.y);
    }
    printf("%lld\n" , ans);
}