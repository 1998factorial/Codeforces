#include <bits/stdc++.h>
#define ID if(0)
using namespace std;
typedef long long ll;
const int INF = 1e9;
int a[85];
int N , nop;
int DP[2][85 * 84 / 2][85][85];
// DP[i][j][k][l] = minimal bad contribution when we process first i elem , with j
// operations, suffix is length k of 0s, given that we have seen l ones
// DP[i][j][k][l] + k -> DP[i + 1][j][k + 1][l] put 0
// DP[i][j][k][l] -> DP[i + 1][j + abs(pos[l] - i - 1)][0][l + 1] put 1
// 85 * 85 * 84 / 2 * 50 * 50
int pos[85];

int main(){
    int i , j , k , l;
    scanf("%d" , &N);
    nop = N * (N - 1) / 2;
    ll nz = 0 , no = 0;
    for(i = 1; i <= N; ++i){
        scanf("%d" , &a[i]) , nz += a[i] == 0;
        if(a[i] == 1){
            pos[++no] = i;
        }
    }
    for(i = 0; i <= 1; ++i){
        for(j = 0; j <= nop; ++j){
            for(k = 0; k <= nz; ++k){
                for(l = 0; l <= no; ++l){
                    DP[i][j][k][l] = INF;
                }
            }
        }
    }
    DP[0][0][0][0] = 0;
    int ans = nz * (nz - 1) / 2;
    for(i = 0; i < N; ++i){
        for(j = 0; j <= nop; ++j){
            for(k = 0; k <= nz; ++k){
                for(l = 0; l <= no; ++l){
                    DP[(i + 1) & 1][j][k][l] = INF;
                }
            }
        }
        for(j = 0; j <= nop; ++j){
            for(k = 0; k <= nz; ++k){
                for(l = 0; l <= no; ++l){
                    int ci = i & 1 , ni = (i + 1) & 1;
                    if(DP[ci][j][k][l] >= INF)continue;
                    // put 0 on i + 1
                    if(k + 1 <= nz)DP[ni][j][k + 1][l] = min(DP[ni][j][k + 1][l] , DP[ci][j][k][l] + k);
                    // put 1 on i + 1
                    if(l + 1 <= no)DP[ni][j + abs(pos[l + 1] - i - 1)][0][l + 1] = min(DP[ni][j + abs(pos[l + 1] - i - 1)][0][l + 1] , DP[ci][j][k][l]);
                }
            }
        }
    }
    int mv = INF;
    for(i = 0; i <= nop; ++i){
        for(j = 0; j <= nz; ++j){
            mv = min(mv , DP[N & 1][i][j][no]);
        }
        printf("%d " , ans - min(ans , mv));
    }
    printf("\n");
}