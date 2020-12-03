#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll MOD = 1e9 + 7;

int K , pa , pb , base , p_a , p_b;
ll DP[2005][2005];
// DP[i][j] = expected number of "ab" subsequences if we
// have i 'a's and j "ab" subsequences so far.
// let p = pa / (pa + pb)
// DP[i][j] = (i + j) + p / (1 - p)
// DP[i][j] = p * DP[i + 1][j] + (1 - p) * DP[i][j + i]

inline ll qpow(ll x , ll n){
    if(n <= 0)return 1;
    ll ret = qpow(x , n / 2);
    ret = ret * ret % MOD;
    if(n & 1)ret = ret * x % MOD;
    return ret;
}

int main(){
    scanf("%d %d %d" , &K , &pa , &pb);
    base = qpow(pa + pb , MOD - 2);
    p_a = (ll)pa * base % MOD;
    p_b = (ll)pb * base % MOD;
    ll p = p_a * qpow((1 - p_a + MOD) % MOD , MOD - 2) % MOD;
    for(int i = 1; i <= K; ++i){
        for(int j = 0; j <= K; ++j){
            if(i + j >= K){
                DP[i][j] = i + j + p;
                DP[i][j] %= MOD;
            }
        }
    }
    for(int i = K; i >= 1; --i){
        for(int j = K; j >= 0; --j){
            if(i + j >= K)continue;
            DP[i][j] += p_a * DP[i + 1][j] % MOD;
            if(DP[i][j] >= MOD)DP[i][j] -= MOD;
            DP[i][j] += p_b * DP[i][i + j] % MOD;
            if(DP[i][j] >= MOD)DP[i][j] -= MOD;
        }
    }
    printf("%lld\n" , DP[1][0]);
}