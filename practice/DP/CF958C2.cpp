#include <bits/stdc++.h>
using namespace std;
const int maxn = 20005;
int DP[maxn][55][105];
int a[maxn];
int N , K , P;
int main(){
    scanf("%d %d %d" , &N , &K , &P);
    for(int i = 1; i <= N; ++i){
        scanf("%d" , &a[i]);
    }
    memset(DP , -1 , sizeof(DP));
    DP[0][0][0] = 0;
    for(int i = 1; i <= N; ++i){
        for(int j = 1; j <= K; ++j){
            for(int k = 0; k < P; ++k){
                if(~DP[i - 1][j][k]){
                    DP[i][j][(k + a[i]) % P] = max(DP[i][j][(k + a[i]) % P] , DP[i - 1][j][k]);
                }
                if(~DP[i - 1][j - 1][k]){
                    DP[i][j][a[i] % P] = max(DP[i][j][a[i] % P] , DP[i - 1][j - 1][k] + k);
                }
            }
        }
    }
    int ret = 0;
    for(int i = 0; i < P; ++i){
        ret = max(ret , DP[N][K][i] + i);
    }
    printf("%d\n" , ret);
}