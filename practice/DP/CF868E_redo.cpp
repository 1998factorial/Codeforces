#include <bits/stdc++.h>
using namespace std;
const int inf = 1e9;
int N , M , s , cnt[55] , DP[55][55][55][55];
vector<array<int , 2>> g[55]; // (to , w)

// we can always catch all criminals
// DP[u][v][n][m] = minimal amount of time to catch all criminals
// if we are at u , from v , n in front of us, m after us

int count(int v , int p){
    int ret = cnt[v];
    for(array<int , 2>& e : g[v]){
        if(e[0] == p)continue;
        ret += count(e[0] , v);
    }
    return ret;
}

int solve(int u , int v , int nf , int nb){
    // at u , from v , nf in front , nb in back
    if(nf == 0 && nb == 0)return 0;
    int& ret = DP[u][v][nf][nb];
    if(~ret)return ret;
    int nc = g[u].size();
    if(nc == 1){
        if(nb == 0)return 0;
        return solve(v , u , nb , 0) + g[u][0][1];
    }
    // we want to minimise the time
    // while the criminals want to maximise the minimal amount of 
    // time we spent, so before we go to u , they would have distributed
    // themselves optimally
    vector<vector<int>> f(nc + 1 , vector<int> (nf + 1 , 0));
    f[0][0] = inf;
    int c = 0;
    for(int i = 0; i < nc; ++i){
        int nu = g[u][i][0] , w = g[u][i][1];
        if(nu != v){
            for(int j = 0; j <= nf; ++j){
                f[c + 1][j] = max(f[c + 1][j] , f[c][j]);
                for(int k = 1; k + j <= nf; ++k){
                    f[c + 1][j + k] = max(f[c + 1][j + k] , min(f[c][j] , w + solve(nu , u , k , nf + nb - k)));
                    //printf("f[%d][%d] = %d\n" , c + 1 , j + k , f[c + 1][j + k]);
                }
            }
            ++c;
        }
    }
    ret = f[nc - 1][nf];
    //printf("DP[%d][%d][%d][%d] = %d\n" , u , v , nf , nb , ret);
    return ret;
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    cin >> N;
    for(int i = 1; i < N; ++i){
        int u , v , w;
        cin >> u >> v >> w;
        g[u].push_back({v , w});
        g[v].push_back({u , w});
    }
    cin >> s;
    cin >> M;
    for(int i = 1; i <= M; ++i){
        int x;
        cin >> x;
        ++cnt[x];
    }
    memset(DP , -1 , sizeof(DP));
    int ret = inf;
    for(array<int , 2>& e : g[s]){
        int v = e[0] , w = e[1] , c = count(v , s) + cnt[s];
        ret = min(ret , solve(v , s , c , M - c) + w);
    }
    cout << ret << endl;
}