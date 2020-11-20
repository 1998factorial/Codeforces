#include <bits/stdc++.h>
#define ID if(0)
using namespace std;
typedef long long ll;
const int MOD = 1e9 + 7;
const int maxn = 2e5 + 10;
ll val[maxn] , ret = 0;
vector<int> g[maxn];
int N , sz[maxn][2] , colour[maxn];
// 1 -> dep % 2 == dep[2] % 2
// 0 -> dep % 2 != dep[2] % 2

void DFS1(int v , int p , int c){
    // colouring & sz pre-compute
    colour[v] = c;
    sz[v][c] = 1;
    for(int u : g[v]){
        if(u != p){
            DFS1(u , v , 1 - c);
            for(int x : {0 , 1}){
                sz[v][x] += sz[u][x];
            }
        }
    }
    ID for(int x : {0 , 1}){
        printf("sz[%d][%d] = %d\n" , v , x , sz[v][x]);
    }
}

void DFS2(int v , int p){
    // solve for v
    ID cout << "v = " << v << endl;
    ret += val[v];
    if(ret >= MOD)ret -= MOD;
    ll B = sz[1][colour[v]] - sz[v][colour[v]] , W = sz[1][1 - colour[v]] - sz[v][1 - colour[v]];
    for(int u : g[v]){
        if(u != p){
            DFS2(u , v);
            ret += (val[v] * B % MOD) * (sz[u][0] + sz[u][1]) % MOD;
            if(ret >= MOD)ret -= MOD;
            ret += (val[v] * sz[u][colour[v]] % MOD) * (B + W) % MOD;
            if(ret >= MOD)ret -= MOD;
            ret -= (val[v] * sz[u][1 - colour[v]] % MOD) * (B + W) % MOD;
            if(ret < 0)ret += MOD;
            ret -= (val[v] * W % MOD) * (sz[u][0] + sz[u][1]) % MOD;
            if(ret < 0)ret += MOD;
            B += sz[u][colour[v]];
            W += sz[u][1 - colour[v]];
        }
    }
    ret += (val[v] * B % MOD) * 2 % MOD;
    if(ret >= MOD)ret -= MOD;
}

int main(){
    scanf("%d" , &N);
    for(int i = 1; i <= N; ++i){
        scanf("%lld" , &val[i]);
    }
    for(int i = 1; i < N; ++i){
        int x , y;
        scanf("%d %d" , &x , &y);
        g[x].push_back(y);
        g[y].push_back(x);
    }
    DFS1(1 , 1 , 1);
    DFS2(1 , 1);
    printf("%lld\n" , (ret % MOD + MOD) % MOD);
}