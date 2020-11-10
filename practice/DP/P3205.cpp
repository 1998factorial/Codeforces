#include <bits/stdc++.h>
#define MOD 19650827
using namespace std;

int N , a[1005];
int DP[1005][1005][2];
// DP[i][j][left/right] = # ways for a[i..j] st, a[i]/a[j] is the last one comming into this seg

int main(){
    scanf("%d" , &N);
    for(int i = 1; i <= N; ++i)scanf("%d" , &a[i]);
    for(int i = 1; i <= N; ++i)DP[i][i][0] = 1;
    for(int len = 2; len <= N; ++len){
        for(int i = 1; i + len - 1 <= N; ++i){
            int j = i + len - 1;
            if(a[i] < a[i + 1])DP[i][j][0] += DP[i + 1][j][0];
            if(DP[i][j][0] >= MOD)DP[i][j][0] -= MOD;
            if(a[i] < a[j])DP[i][j][0] += DP[i + 1][j][1];
            if(DP[i][j][0] >= MOD)DP[i][j][0] -= MOD;
            if(a[j] > a[j - 1])DP[i][j][1] += DP[i][j - 1][1];
            if(DP[i][j][1] >= MOD)DP[i][j][1] -= MOD;
            if(a[j] > a[i])DP[i][j][1] += DP[i][j - 1][0];
            if(DP[i][j][1] >= MOD)DP[i][j][1] -= MOD;
        }
    }
    printf("%d\n" , (DP[1][N][0] + DP[1][N][1]) % MOD);
}