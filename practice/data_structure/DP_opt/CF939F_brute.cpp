#include <bits/stdc++.h>
#define ID if(0)
using namespace std;
const int INF = 1e9;
const int maxn = 1e5 + 10;
int N , K;
int L[105] , R[105];
int DP[105][2 * maxn];
// DP[i][j] = minimal flips when we process up to time = R[i] with total exposed time of current side = j

int main(){
    int i , j , t;
    scanf("%d %d" , &N , &K);
    for(i = 1; i <= K; ++i){
        scanf("%d %d" , &L[i] , &R[i]);
    }
    for(i = 0; i <= K; ++i){
        for(j = 0; j <= 2 * N; ++j){
            DP[i][j] = INF;
        }
    }
    // DP[i][j] = min{DP[i][j - (R[i] - R[i - 1])]}
    // DP[i][j] = min{1 + DP[i - 1][R[i - 1] + t - j] , 0 <= t <= R[i] - L[i]}
    // DP[i][j] = min{2 + DP[i - 1][j - R[i] + R[i - 1] + t] , 0 <= t <= R[i] - L[i]}
    DP[0][0] = 0;
    for(i = 1; i <= K; ++i){
        for(j = 0; j <= 2 * N && j <= R[i]; ++j){
            if(j - R[i] + R[i - 1] >= 0)
                DP[i][j] = min(DP[i][j] , DP[i - 1][j - R[i] + R[i - 1]]);
            for(t = 0; t <= R[i] - L[i]; ++t){
                if(R[i - 1] + t - j >= 0)
                    DP[i][j] = min(DP[i][j] , 1 + DP[i - 1][R[i - 1] + t - j]);
                if(j - R[i] + R[i - 1] + t >= 0)
                    DP[i][j] = min(DP[i][j] , 2 + DP[i - 1][j - R[i] + R[i - 1] + t]);
            }
            ID printf("DP[%d][%d] = %d\n" , i , j , DP[i][j]);
        }
    }
    if(R[K] - N < 0 || DP[K][R[K] - N] >= INF){
        printf("Hungry\n");
    }
    else{
        printf("Full\n%d\n" , DP[K][R[K] - N]);
    }   
}