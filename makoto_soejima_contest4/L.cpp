/*
    say s[i] match with t[j] in an optimal solution
    We can insert any string after s[i] as long as t[j] != t[j + 1]
    so let DP[i][j] = can we do for s[i..N] and t[j..M] ?
    if s[i] == t[j] : DP[i][j] = DP[i + 1][j + 1] || (t[j] != t[j + 1] && (DP[i + 1][j + 2] || .. || DP[i + 1][M]))
    the accumulation can be maintained by a suffix or sum array.
*/
#include <bits/stdc++.h>
#define ID if(0)
using namespace std;
const int maxn = 5005;
char s[maxn] , t[maxn];
int DP[maxn][maxn];
int sum[maxn][maxn];
int N , M;

bool solve(){
    int i , j;
    DP[N + 1][M + 1] = 1;
    for(i = 1; i <= M + 1; ++i)sum[N + 1][i] = 1;
    for(i = N; i >= 1; --i){
        for(j = M; j >= 1; --j){
            if(N - i > M - j)continue;
            if(s[i] == t[j]){
                DP[i][j] |= DP[i + 1][j + 1] || (t[j] != t[j + 1] && sum[i + 1][j + 1]);
            }
            sum[i][j] = DP[i][j] || sum[i][j + 1];
        }
    }
    ID for(int i = N; i >= 1; --i){
        for(int j = M; j >= 1; --j){
            printf("DP[%d][%d] = %d\n" , i , j , DP[i][j]);
        }
    }
    return DP[1][1];
}

int main(){
    scanf("%s" , s + 1);
    scanf("%s" , t + 1);
    N = strlen(s + 1);
    M = strlen(t + 1);
    printf("%s\n" , solve() ? "Yes" : "No");
}