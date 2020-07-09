#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<ll , ll> ii;

const int maxn = 2e3 + 10;
const ll mod = 1e9 + 7;
const ll INF = 1e18;
int N , M , Q;
vector<ii> g[maxn];
ll DP[maxn][maxn];

int main(){
    scanf("%d %d %d" , &N , &M , &Q);
    for(int i = 1; i <= M; ++i){
        int x , y , z;
        scanf("%d %d %d" , &x , &y , &z);
        g[x].emplace_back(y , z);
        g[y].emplace_back(x , z);
    }
    for(int v = 1; v <= N; ++v){
        for(int j = 0; j <= M; ++j){
            DP[v][j] = -1;
        }
    }
    DP[1][0] = 0;
    for(int j = 1; j <= M; ++j){
        for(int v = 1; v <= N; ++v){
            for(auto& e : g[v]){
                int u = e.first , w = e.second;
                if(DP[u][j - 1] == -1)continue;
                DP[v][j] = max(DP[v][j] , DP[u][j - 1] + w);
            }
        }
    }
    for(int q = 1; q <= Q; ++q){
        ll mx = -INF;
        for(int v = 1; v <= N; ++v){
            mx = max(mx , DP[v][q]);
        }
        printf("q = %d , max = %lld\n" , q , mx);
    }
}
