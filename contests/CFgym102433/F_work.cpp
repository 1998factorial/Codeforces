#include <bits/stdc++.h>
#define INF 1180591620717411303424.0
using namespace std;
typedef long double ld;
const int maxn = 52;
int N , M;
long long K;
ld C[maxn][maxn] , DP[maxn][maxn][maxn];
// DP[i][j][k] = number of ways to allocate i elements, if we want to make
// j fix points, and we can make k fix points at most (i >= k >= j)

int main(){
    scanf("%d %d %lld" , &N , &M , &K);
    C[0][0] = 1;
    for(int i = 1; i <= N; ++i){
        for(int j = 0; j <= i; ++j){
            if(j == 0 || i == j)C[i][j] = 1;
            else {
                C[i][j] += C[i - 1][j];
                C[i][j] += C[i - 1][j - 1];
                if(C[i][j] > INF)C[i][j] = INF;
            }
        }
    }
    DP[0][0][0] = 1;
    for(int i = 1; i <= N; ++i){
        if(DP[i - 1][0][0] >= INF)DP[i][0][0] = INF;
        else {
            DP[i][0][0] = DP[i - 1][0][0] * i;
            if(DP[i][0][0] > INF)DP[i][0][0] = INF;
        }
    }
    // for j > 0 : DP[i][j][k] = C[k][j] * DP[i - j][0][k - j] 
    // for j == 0 : DP[i][j][k] = (k - 1) * DP[i - 1][j][k - 2] + (i - k) * DP[i - 1][j][k - 1]
    for(int i = 1; i <= N; ++i){ // i elememts left
        for(int k = 1; k <= i; ++k){ // k can be fixed point
            for(int j = 0; j <= k; ++j){ // j must be fixed point
                if(j == 0){
                    if(k - 2 >= 0){
                        if(DP[i - 1][j][k - 2] > INF)DP[i][j][k] = INF;
                        else{
                            DP[i][j][k] += DP[i - 1][j][k - 2] * (k - 1);
                            if(DP[i][j][k] > INF)DP[i][j][k] = INF;
                        }
                    }
                    if(k - 1 >= 0){
                        if(DP[i - 1][j][k - 1] > INF && i - k > 0)DP[i][j][k] = INF;
                        else{
                            DP[i][j][k] += DP[i - 1][j][k - 1] * (i - k);
                            if(DP[i][j][k] > INF)DP[i][j][k] = INF;
                        }
                    }
                }
                else{
                    if(C[k][j] > INF || DP[i - j][0][k - j] > INF){
                        DP[i][j][k] = INF;
                    }
                    else{
                        DP[i][j][k] += C[k][j] * DP[i - j][0][k - j];
                        if(DP[i][j][k] > INF)DP[i][j][k] = INF;
                    }
                }
            }
        }
    }
    vector<int> ans(N + 1);
    vector<int> used(N + 1);
    int k = N;
    for(int i = 1; i <= N; ++i){    
        for(int j = 1; j <= N; ++j){
            if(used[j])continue;
            if(i == j && M){
                // can we make a fix point here ?
                if(DP[N - i][M - 1][k - 1] >= K){ // we can
                    --M;
                    --k;
                    ans[i] = j;
                    used[j] = 1;
                    break;
                }
                else{ // we can not
                    K -= DP[N - i][M - 1][k - 1];
                }
            }
            else if(i != j){
                int nk = k;
                if(j > i)--nk;
                if(!used[i])--nk;
                if(DP[N - i][M][nk] >= K){
                    k = nk;
                    ans[i] = j;
                    used[j] = 1;
                    break;
                }
                else{
                    K -= DP[N - i][M][nk];
                }
            }
        }
        if(!ans[i]){
            printf("-1\n");
            return 0;
        }
    }
    for(int i = 1; i <= N; ++i)printf("%d " , ans[i]);
    printf("\n");
}