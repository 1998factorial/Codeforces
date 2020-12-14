#include <bits/stdc++.h>
#define pb push_back
#define rep(i , a , b) for(int i = a; i <= b; ++i)
using namespace std;
typedef long long ll;
const int MOD = 1e9 + 7;
int N , M , sz[2005] , ncycle = 0 , cnt , DP[2005][4010][2][2];
vector<int> g[2005];
bool vis[2005];
// DP[i][j][k][x] = # ways that for the first cycles, # red - # blue = j ,
// (k , x) , (0 , 0) => they have not met on the cycle , (0 , 1) => they have met on some 
// cycle, (1 , 0) => they meet at point 1, (1 , 1) => they meet at some edge incident to 1
void DFS(int v , int p){
    vis[v] = 1;
    ++cnt;
    for(int u : g[v]){
        if(u == p)continue;
        if(vis[u])continue;
        DFS(u , v);
    }
}

void add(int& x , int y){
    x += y;
    if(x >= MOD)x -= MOD;
}

int main(){
    scanf("%d %d" , &N , &M);
    rep(i , 1 , M){
        int u , v;
        scanf("%d %d" , &u , &v);
        g[u].pb(v);
        g[v].pb(u);
    }
    vis[1] = 1;
    rep(v , 2 , N){
        if(vis[v])continue;
        cnt = 1;
        DFS(v , v);
        sz[++ncycle] = cnt;
    }
    DP[0][N][0][0] = DP[0][N][1][0] = 1;
    int lim = 0;
    rep(i , 1 , ncycle){
        rep(j , -lim , lim){
            int cj = j + N;
            rep(k , 0 , 1){
                if(k == 0){
                    rep(x , 0 , 1){ // either not met yet or meet but not cycle i
                        add(DP[i][cj + sz[i]][k][x] , DP[i - 1][cj][k][x]);
                        add(DP[i][cj - sz[i]][k][x] , DP[i - 1][cj][k][x]);
                        add(DP[i][cj][k][x] , DP[i - 1][cj][k][x]);
                    }
                    rep(r , 1 , sz[i] - 1){ // meet on cycle i's vertex
                        int b = sz[i] - r;
                        add(DP[i][cj + r - b][k][1] , 2ll * DP[i -  1][cj][k][0] % MOD);
                    }
                    rep(r , 1 , sz[i] - 2){ // meet on cycle i's edge
                        int b = sz[i] - 1 - r;
                        add(DP[i][cj + r - b][k][1] , 2ll * DP[i - 1][cj][k][0] % MOD);
                    }
                }
                else{
                    // we will meet either at vertex 1 or an edge incident to vertex 1
                    rep(x , 0 , 1){ // not this cycle
                        add(DP[i][cj + sz[i]][k][x] , DP[i - 1][cj][k][x]);
                        add(DP[i][cj - sz[i]][k][x] , DP[i - 1][cj][k][x]);
                    }
                    // for this cycle
                    add(DP[i][cj + sz[i] - 1][k][1] , 2ll * DP[i - 1][cj][k][0] % MOD);
                    add(DP[i][cj - sz[i] + 1][k][1] , 2ll * DP[i - 1][cj][k][0] % MOD);
                }
            }
        }
        lim += sz[i];
    }
    ll ret = 0;
    rep(i , 0 , 1){
        rep(j , 0 , 1){
            if(!i && !j)continue;
            ret += DP[ncycle][N][i][j];
            if(ret >= MOD)ret -= MOD;
        }
    }
    printf("%lld\n" , ret);
}