#include <bits/stdc++.h>
using namespace std;
const int INF = 1e9 + 10;
int N , M;
int a[1010][5010] , sum[1010][5010] , ladder[1010][15] , sz[1010];
int DP[1010][15][15] , L[1010][5010] , R[1010][5010];
// DP[i][l][k] = maximal amount of candy we get
// if we go down to level i using the l-th ladder
// , leaving level i using r-th ladder

int getsum(int row , int l , int r){
    if(r < l)return 0;
    return sum[row][r] - sum[row][l - 1];
}

int main(){
    char tmp[5010];
    scanf("%d %d" , &N , &M);
    for(int i = 1; i <= N; ++i){
        scanf("%s" , tmp + 1);
        for(int j = 1; j <= M; ++j){
            if('0' <= tmp[j] && tmp[j] <= '9'){
                a[i][j] = tmp[j] - '0';
            }
        }
        for(int j = 1; j <= M; ++j){
            sum[i][j] = sum[i][j - 1] + a[i][j];
        }
        scanf("%s" , tmp + 1);
        for(int j = 1; j <= M; ++j){
            if(tmp[j] == '|'){
                ladder[i][++sz[i]] = j;
            }
        }
    }
    for(int i = 1; i <= N; ++i){
        L[i][1] = 1;
        for(int j = 2; j <= M; ++j){
            if(a[i][j]) L[i][j] = j;
            else L[i][j] = L[i][j - 1];
        }
        R[i][M] = M;
        for(int j = M - 1; j >= 1; --j){
            if(a[i][j]) R[i][j] = j;
            else R[i][j] = R[i][j + 1];
        }
    }
    for(int i = 1; i <= N; ++i){
        for(int j = 1; j <= sz[i]; ++j){
            for(int k = j; k <= sz[i]; ++k){
                DP[i][j][k] = -INF;
            }
        }
    }
    for(int i = N; i >= 1; --i){
        for(int l = 1; l <= sz[i]; ++l){
            for(int r = l; r <= sz[i]; ++r){
                DP[i][l][r] = max(DP[i][l][r] , getsum(i + 1 , L[i + 1][ladder[i][l]] , R[i + 1][ladder[i][r]]));
                if(l == r && a[i + 1][ladder[i][l]])continue;
                for(int nl = 1; nl <= sz[i + 1]; ++nl){
                    for(int nr = nl; nr <= sz[i + 1]; ++nr){
                        if(ladder[i][l] >= ladder[i + 1][nr] && getsum(i + 1 , ladder[i + 1][nr] , ladder[i][l]) > 0)continue;
                        if(ladder[i + 1][nl] >= ladder[i][r] && getsum(i + 1 , ladder[i][r] , ladder[i + 1][nl]) > 0)continue;
                        if(nl == nr && a[i + 1][ladder[i + 1][nl]])continue;
                        int l_outer = L[i + 1][min(ladder[i][l] , ladder[i + 1][nl])];
                        int r_inner = L[i + 1][min(ladder[i][r] , ladder[i + 1][nr])];
                        int r_outer = R[i + 1][max(ladder[i][r] , ladder[i + 1][nr])];
                        int l_inner = R[i + 1][max(ladder[i][l] , ladder[i + 1][nl])];
                        DP[i][l][r] = max(DP[i][l][r] , DP[i + 1][nl][nr] + getsum(i + 1 , l_outer , r_outer) - getsum(i + 1 , l_inner + 1 , r_inner - 1));
                    }
                }
            }
        }
    }
    int ret = 0;
    for(int l = 1; l <= sz[1]; ++l){
        for(int r = l; r <= sz[1]; ++r){
            ret = max(ret , DP[1][l][r]);
        }
    }
    printf("%d\n" , ret);
}