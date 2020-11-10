#include <bits/stdc++.h>
#define ID if(1)
using namespace std;
const int INF = 1e9;
int DP[2][4005][2005]; 
// DP[i][j][k] = maximal profit if we process last i ppl, where the maximal agg = j, and there are k of them
// we can update DP[i][l[i]][k] first, then using this DP[i][j][k] to update DP[i][j + 1][k / 2], for j >= l[i]
int N , M;
int l[2005] , s[2005] , c[4005];

int main(){
    int i , j , k;
    scanf("%d%d" , &N , &M);
    // reverse final cost = normal final cost
    // we need to find a non-decreasing sequence
    for(i = N; i >= 1; --i)scanf("%d" , &l[i]);
    for(i = N; i >= 1; --i)scanf("%d" , &s[i]);
    for(i = 1; i <= N + M; ++i)scanf("%d" , &c[i]);
    for(i = 0; i <= 1; ++i){
        for(j = 1; j <= N + M; ++j){
            for(k = 1; k <= N; ++k){
                DP[i][j][k] = -INF;
            }
        }
    }
    for(i = 1; i <= N; ++i){
        int mv = l[i];
        for(j = 0; j <= N + M; ++j){
            for(k = 0; k <= i; ++k){
                // O(N * (N + M) * N), we need to get rid off this 
                DP[i & 1][j][k] = max(DP[i & 1][j][k] , DP[(i - 1) & 1][j][k]);
            }
        }
        for(k = 1; k <= i; ++k){
            DP[i & 1][mv][k] = max(DP[i & 1][mv][k] , DP[(i - 1) & 1][mv][k - 1] + c[mv] - s[i]);
        }
        for(j = mv; j <= N + M; ++j){
            for(k = i >> (j - mv); k >= 0; --k){
                DP[i & 1][j + 1][k / 2] = max(DP[i & 1][j + 1][k / 2] , DP[i & 1][j][k] + (k / 2) * c[j + 1]);
            }
        }
    }
    int ans = 0;
    for(i = 1; i <= N + M; ++i){
        for(j = 0; j < 2; ++j){
            ans = max(ans , DP[N & 1][i][j]);
        }
    }
    printf("%d\n" , ans);
}