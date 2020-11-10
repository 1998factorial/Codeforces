#include <bits/stdc++.h>
using namespace std;
const int INF = 1e9;
int N;
int a[5005];
int DP[5005][2555][2];
// [1] -> house at i
// [0] -> no house
// DP[i][j][0] = min{DP[i - 1][j][0] , DP[i - 1][j][1] + a[i] - min{a[i] - a[i - 1] + 1}}
// DP[i][j][1] = min{DP[i - 2][j - 1][0] + a[i - 1] - min{a[i - 1] , a[i] - 1}, DP[i - 2][j - 1][1] + min(a[i - 1] , a[i - 2] - 1) , a[i] - 1}}
int main(){
    scanf("%d" , &N);
    int i , j , lim = N / 2 + N % 2 , k;
    for(i = 1; i <= N; ++i)scanf("%d" , &a[i]);
    a[0] = -INF;
    a[N + 1] = -INF;
    for(i = 0; i <= N + 1; ++i){
        for(j = 0; j <= lim; ++j){
            for(k = 0; k < 2; ++k){
                DP[i][j][k] = INF;
            }
        }   
    }
    DP[0][0][0] = 0;
    for(i = 1; i <= N + 1; ++i)DP[i][0][0] = 0;
    for(i = 1; i <= N + 1; ++i){
        for(j = 1; j <= lim && j <= i; ++j){
            DP[i][j][0] = min(DP[i][j][0] , DP[i - 1][j][0]);
            DP[i][j][0] = min(DP[i][j][0] , DP[i - 1][j][1]);
            if(i > 1){
                DP[i][j][1] = min(DP[i][j][1] , DP[i - 2][j - 1][0] + a[i - 1] - min(a[i - 1] , a[i] - 1) + a[i + 1] - min(a[i + 1] , a[i] - 1));
                DP[i][j][1] = min(DP[i][j][1] , DP[i - 2][j - 1][1] + min(a[i - 1] , a[i - 2] - 1) - min(min(a[i - 1] , a[i - 2] - 1) , a[i] - 1) + a[i + 1] - min(a[i + 1] , a[i] - 1));
            }
            else if(i == 1){
                DP[i][j][1] = min(DP[i - 1][j - 1][0] + a[2] - min(a[2] , a[1] - 1) , DP[i][j][1]);
            }
        }
    }
    for(i = 1; i <= lim; ++i){
        printf("%d " , DP[N + 1][i][0]);
    }
    printf("\n");
}