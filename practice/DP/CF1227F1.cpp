#include <bits/stdc++.h>
#define MOD 998244353
using namespace std;
typedef long long ll;
int N , K;
int a[2005] , b[2005];
ll DP[2005][5000];
// DP[i][j] = # of length i sequence st # match b - # match a = j
int base = 2005;

int main(){
    scanf("%d%d" , &N , &K);
    for(int i = 1; i <= N; ++i){
        scanf("%d" , &a[i]);
        if(i - 1 >= 1)b[i - 1] = a[i];
        else b[N] = a[i];
    }
    DP[0][base] = 1;
    for(int i = 0; i < N; ++i){
        for(int j = -i; j <= i; ++j){
            int cj = j + base;
            // # match b > # match a
            if(a[i + 1] == b[i + 1]){
                DP[i + 1][cj] += DP[i][cj] * K % MOD;
                if(DP[i + 1][cj] >= MOD)DP[i + 1][cj] -= MOD; 
            }
            else{
                DP[i + 1][cj] += DP[i][cj] * (K - 2) % MOD;
                if(DP[i + 1][cj] >= MOD)DP[i + 1][cj] -= MOD;
                DP[i + 1][cj + 1] += DP[i][cj];
                if(DP[i + 1][cj + 1] >= MOD)DP[i + 1][cj + 1] -= MOD;
                DP[i + 1][cj - 1] += DP[i][cj];
                if(DP[i + 1][cj - 1] >= MOD)DP[i + 1][cj - 1] -= MOD;
            }
        }
    }
    ll ret = 0;
    for(int j = 1; j <= N; ++j){
        ret += DP[N][j + base];
        if(ret >= MOD)ret -= MOD;
    }
    printf("%lld\n" , ret);
}