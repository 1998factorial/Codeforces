#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll MOD = 1e9 + 7;
int N , M;
vector<int> g[2005];
int a[2005] , cnt , tot = 0 , DP[2005][4010][5];
bool vis[2005];
// 0 : have not met yet
// 1 : met on some vertex in some cycle
// 2 : met on some edge in some cycle
// 3 : met on vertex 1
// 4 : met on some edge incident to vertex 1
// DP[i][j][k] = # of configurations for first i cycles, #red - #blue = j, flag = k
void DFS(int v , int p){
    vis[v] = 1;
    ++cnt;
    for(int u : g[v]){
        if(!vis[u]){
            DFS(u , v);
        }
    }
}

int main(){
    scanf("%d %d" , &N , &M);
    for(int i = 1; i <= M; ++i){
        int u , v;
        scanf("%d %d" , &u , &v);
        g[u].push_back(v);
        g[v].push_back(u);
    }
    vis[1] = 1;
    for(int v = 2; v <= N; ++v){
        if(!vis[v]){
            cnt = 0;
            DFS(v , v);
            a[++tot] = cnt + 1;
        }
    }
    DP[0][N][0] = 1;
    DP[0][N][3] = 1;
    int lim = 0;
    for(int i = 1; i <= tot; ++i){
        for(int j = -lim; j <= lim; ++j){
            // not met yet
            // current cycle is red
            DP[i][j + N + a[i]][0] = ((ll)DP[i][j + N + a[i]][0] + DP[i - 1][j + N][0]) % MOD;
            // current cycle is blue
            DP[i][j + N - a[i]][0] = ((ll)DP[i][j + N - a[i]][0] + DP[i - 1][j + N][0]) % MOD;
            // current cycle is not taken
            DP[i][j + N][0] = ((ll)DP[i][j + N][0] + DP[i - 1][j + N][0]) % MOD; 

            // meet on some vertex in some cycle(not cycle[i])
            DP[i][j + N + a[i]][1] = ((ll)DP[i][j + N + a[i]][1] + DP[i - 1][j + N][1]) % MOD;
            // current cycle is blue
            DP[i][j + N - a[i]][1] = ((ll)DP[i][j + N - a[i]][1] + DP[i - 1][j + N][1]) % MOD;
            // current cycle is not taken
            DP[i][j + N][1] = ((ll)DP[i][j + N][1] + DP[i - 1][j + N][1]) % MOD; 

            // meet on some edge in some cycle(not cycle[i])
            DP[i][j + N + a[i]][2] = ((ll)DP[i][j + N + a[i]][2] + DP[i - 1][j + N][2]) % MOD;
            // current cycle is blue
            DP[i][j + N - a[i]][2] = ((ll)DP[i][j + N - a[i]][2] + DP[i - 1][j + N][2]) % MOD;
            // current cycle is not taken
            DP[i][j + N][2] = ((ll)DP[i][j + N][2] + DP[i - 1][j + N][2]) % MOD; 
        
            // we met on some vertex of this cycle
            for(int k = 1; k < a[i]; ++k){
                // k edges are red , a[i] - k are blue
                int nj = j + N + k - (a[i] - k);
                DP[i][nj][1] = ((ll)DP[i][nj][1] + 2ll * DP[i - 1][j + N][0] % MOD) % MOD; // (R , B) (B , R)
            }

            // we met on some edge of this cycle
            for(int k = 1; k < a[i] - 1; ++k){
                // k edges are red , a[i] - 1 - k are blue
                int nj = j + N + k - (a[i] - 1 - k);
                DP[i][nj][2] = ((ll)DP[i][nj][2] + 2ll * DP[i - 1][j + N][0] % MOD) % MOD; // (R , B) (B , R)
            }

            // met on vertex 1
            DP[i][j + N + a[i]][3] = ((ll)DP[i][j + N + a[i]][3] + DP[i - 1][j + N][3]) % MOD;
            DP[i][j + N - a[i]][3] = ((ll)DP[i][j + N - a[i]][3] + DP[i - 1][j + N][3]) % MOD;
            
            // met on some edge incident to vertex 1, but not this cycle
            DP[i][j + N + a[i]][4] = ((ll)DP[i][j + N + a[i]][4] + DP[i - 1][j + N][4]) % MOD;
            DP[i][j + N - a[i]][4] = ((ll)DP[i][j + N - a[i]][4] + DP[i - 1][j + N][4]) % MOD;

            // met on some edge incident to vertex 1 and it is this cycle , we would need to take all cycles
            DP[i][j + N + a[i] - 1][4] = ((ll)DP[i][j + N + a[i] - 1][4] + 2ll * DP[i - 1][j + N][3] % MOD) % MOD; // 2 directions
            DP[i][j + N - a[i] + 1][4] = ((ll)DP[i][j + N - a[i] + 1][4] + 2ll * DP[i - 1][j + N][3] % MOD) % MOD; // 2 directions   
        }
        lim += a[i];
    }
    ll ret = 0;
    for(int i = 1; i <= 4; ++i){
        ret += DP[tot][N][i];
        if(ret >= MOD)ret -= MOD;
    }
    printf("%lld\n" , ret);
}   