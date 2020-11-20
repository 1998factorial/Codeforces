#include <bits/stdc++.h>
using namespace std;
const int INF = 1e9;
int N , K , S;
int a[155];
int DP[2][155][155 * 155];
// DP[i][j][k] = minimal sum of building length j prefix
// using a[1..i], given that we have swapped k times
// in optimal solution, for all i in ANS , p[i] <= i  (no cross/relative order unchange , as it costs more swaps)
// so we have no after effect
int main(){
    scanf("%d%d%d" , &N , &K , &S);
    for(int i = 1; i <= N; ++i){
        scanf("%d" , &a[i]);
    }
    S = min(S , N * N);
    for(int i = 0; i <= 1; ++i){
        for(int j = 0; j <= K; ++j){
            for(int k = 0; k <= S; ++k){
                DP[i][j][k] = INF;
            }
        }
    }
    DP[0][0][0] = 0;
    for(int i = 0; i < N; ++i){
        int ci = i & 1 , ni = (i + 1) & 1;
        for(int j = 0; j <= K; ++j){
            for(int k = 0; k <= S; ++k){
                DP[ni][j][k] = INF;
            }
        }
        for(int j = 0; j <= K; ++j){
            for(int k = 0; k <= S; ++k){
                // DP[i][j][k] can go to ?
                if(DP[ci][j][k] == INF)continue;
                // if we ignore a[i + 1]
                DP[ni][j][k] = min(DP[ni][j][k] , DP[ci][j][k]);
                // if we put a[i + 1] at pos = j + 1
                if(j + 1 <= K){
                    if(i >= j && k + i - j <= S){
                        DP[ni][j + 1][k + i - j] = min(DP[ni][j + 1][k + i - j] , DP[ci][j][k] + a[i + 1]);
                    }
                }
            }
        }
    }
    int ret = INF;
    for(int i = 0; i <= S; ++i){
        ret = min(ret , DP[N & 1][K][i]);
    }
    printf("%d\n" , ret);
}