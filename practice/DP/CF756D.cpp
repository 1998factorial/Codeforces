#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll MOD = 1e9 + 7;
int N , M = 0;
char a[5005] , b[5005];
ll fac[5005] , inv[5005] , DP[2][5005][26];

inline ll qpow(ll x , ll n){
    if(n <= 0)return 1;
    ll ret = qpow(x , n / 2);
    ret = ret * ret % MOD;
    if(n & 1)ret = ret * x % MOD;
    return ret;
}

ll C(int n , int r){
    if(n < r || n < 0 || r < 0)return 0;
    return fac[n] * (inv[n - r] * inv[r] % MOD) % MOD;
}

int main(){
    scanf("%d" , &N);
    scanf("%s" , (a + 1));
    fac[0] = 1; inv[0] = qpow(fac[0] , MOD - 2);
    for(int i = 1; i <= N; ++i)fac[i] = fac[i - 1] * i % MOD , inv[i] = qpow(fac[i] , MOD - 2);
    for(int i = 1; i <= N; ++i){
        if(a[i] != a[i - 1]){
            b[++M] = a[i];
        }
    }
    // DP[i][j][k] = number of sequence using b[1..i], with j blocks, ends with b[]
    // such that no adjcent blocks are the same
    for(int i = 1; i <= M; ++i){
        int ci = i & 1 , pi = (i - 1) & 1 , x = b[i] - 'a';
        for(int j = 0; j <= i; ++j){
            for(int k = 0; k < 26; ++k){
                DP[ci][j][k] = DP[pi][j][k];
            }
        }
        for(int j = 1; j <= i; ++j){
            for(int k = 0; k < 26; ++k){
                if(k != x){
                    DP[ci][j][x] += DP[pi][j - 1][k];
                    if(DP[ci][j][x] >= MOD)DP[ci][j][x] -= MOD; 
                }
            }
            DP[ci][j][x] -= DP[pi][j][x];
            if(DP[ci][j][x] < 0)DP[ci][j][x] += MOD;
        }
        if(DP[ci][1][x] == 0)DP[ci][1][x] = 1;
    }
    ll ret = 0;
    for(int i = 1; i <= M; ++i){
        for(int j = 0; j < 26; ++j){
            ret += DP[M & 1][i][j] * C(N - 1 , i - 1) % MOD;
            if(ret >= MOD)ret -= MOD;
        }
    }
    printf("%lld\n" , ret);
}