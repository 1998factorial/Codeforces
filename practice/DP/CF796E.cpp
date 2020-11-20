#include <bits/stdc++.h>
using namespace std;
int N , P , K , len;
int a[1005] , b[1005];
int DP[2][1005][55][55];
//DP[i][j][x][y] = maximal number of questions I can get 
//for the first i questions, cheated j times, 
//we can get x free questions from a
//we can get y free questions from b
//note that j is up to min(P , 2 * ceil(N / K)) as we can cover everything there
//time complexity O(N*(N/K)*K*K) = O(N^2*K)
int main(){
    scanf("%d %d %d" , &N , &P , &K);
    scanf("%d" , &len);
    for(int i = 1; i <= len; ++i){
        int x;
        scanf("%d" , &x);
        a[x] = 1;
    }
    scanf("%d" , &len);
    for(int i = 1; i <= len; ++i){
        int x;
        scanf("%d" , &x);
        b[x] = 1;
    }
    P = min(P , 2 * (N / K + (N % K != 0)));
    memset(DP , -1 , sizeof(DP));
    DP[0][0][0][0] = 0;
    for(int i = 0; i < N; ++i){
        int ni = (i + 1) & 1;
        int ci = i & 1;
        for(int j = 0; j <= P; ++j){
            for(int x = 0; x <= K; ++x){
                for(int y = 0; y <= K; ++y){
                    DP[ni][j][x][y] = -1;
                }
            }
        }
        for(int j = 0; j <= P; ++j){
            for(int x = 0; x <= K; ++x){
                for(int y = 0; y <= K; ++y){
                    if(DP[ci][j][x][y] == -1)continue;
                    if(x && y){
                        DP[ni][j][x - 1][y - 1] = max(DP[ni][j][x - 1][y - 1] , DP[ci][j][x][y] + (a[i + 1] || b[i + 1]));
                        // it is optimal to cheat when we are running low
                    }
                    if(!x && !y){
                        // do not cheat extra
                        DP[ni][j][x][y] = max(DP[ni][j][x][y] , DP[ci][j][x][y]);
                        if(j + 1 <= P){
                            // cheat on a
                            DP[ni][j + 1][K - 1][y] = max(DP[ni][j + 1][K - 1][y] , DP[ci][j][x][y] + a[i + 1]);
                            // cheat on b
                            DP[ni][j + 1][x][K - 1] = max(DP[ni][j + 1][x][K - 1] , DP[ci][j][x][y] + b[i + 1]);
                        }
                        if(j + 2 <= P){
                            // cheat on a and b
                            DP[ni][j + 2][K - 1][K - 1] = max(DP[ni][j + 2][K - 1][K - 1] , DP[ci][j][x][y] + (a[i + 1] || b[i + 1]));
                        }
                    }
                    if(!x && y){
                        // do not cheat extra
                        DP[ni][j][x][y - 1] = max(DP[ni][j][x][y - 1] , DP[ci][j][x][y] + b[i + 1]);
                        if(j + 1 <= P){
                            DP[ni][j + 1][K - 1][y - 1] = max(DP[ni][j + 1][K - 1][y - 1] , DP[ci][j][x][y] + (a[i + 1] || b[i + 1]));
                        }
                        // we do not need to cheat extra on b
                    }
                    if(x && !y){
                        DP[ni][j][x - 1][y] = max(DP[ni][j][x - 1][y] , DP[ci][j][x][y] + a[i + 1]);
                        if(j + 1 <= P){
                            DP[ni][j + 1][x - 1][K - 1] = max(DP[ni][j + 1][x - 1][K - 1] , DP[ci][j][x][y] + (a[i + 1] || b[i + 1]));
                        }
                    }
                }
            }
        }
    }
    int ret = 0;
    for(int i = 0; i <= P; ++i){
        for(int j = 0; j <= K; ++j){
            for(int k = 0; k <= K; ++k){
                ret = max(ret , DP[N & 1][i][j][k]);
            }
        }
    }
    printf("%d\n" , ret);
}