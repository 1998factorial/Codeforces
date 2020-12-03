#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int maxn = 3e3 + 10;
vector<int> g[maxn];
int N , sz[maxn][maxn] , up[maxn][maxn];
ll DP[maxn][maxn];
//DP[v][u] = maximal sum of mex for the chain starting at v ending at u
//sz[v][p] = size of the subtree rooted at v given p is the ancestor of v
//up[v][p] = u , u is the direct ancestor of v given p is the ancestor of v and u

// count # paths st mex(x,y) >= some i for the total contribution
// notice that the answer looks like a chain
// so it make sense to enumerate the end points of the chain using DP
// also observe that the larger value should appear at the edge of the chain
// so that sum of mex is maximised

void getsz(int v , int p , int ancestor){
    int& val = sz[v][ancestor];
    val = 1;
    for(int u : g[v]){
        if(u != p){
            getsz(u , v , ancestor);
            val += sz[u][ancestor];
            up[u][ancestor] = v;
        }
    }
}

ll solve(int l , int r){
    if(l == r){
        DP[l][r] = 0;
        return 0;
    }
    ll& ret = DP[l][r];
    if(~ret){
        return ret;
    }
    // we choose to put the current largest weight on either
    // (l , up[l][r]) or (up[r][l] , r)
    ret = (ll)sz[l][r] * sz[r][l] + max(solve(l , up[r][l]) , solve(up[l][r] , r));
    return ret;
}

int main(){
    scanf("%d"  , &N);
    for(int i = 1; i < N; ++i){
        int u , v;
        scanf("%d %d" , &u , &v);
        g[u].push_back(v);
        g[v].push_back(u);
    }
    for(int i = 1; i <= N; ++i){
        up[i][i] = i;
        getsz(i , i , i);
    }
    memset(DP , -1 , sizeof(DP));
    ll ret = 0;
    for(int u = 1; u <= N; ++u){
        for(int v = 1; v <= N; ++v){
            ret = max(ret , solve(u , v));
        }
    }
    printf("%lld\n" , ret);
}