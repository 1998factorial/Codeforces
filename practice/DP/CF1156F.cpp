#include <bits/stdc++.h>
#define ID if(0)
using namespace std;
typedef long long ll;
const ll MOD = 998244353;

int N , a[5005] , cnt[5005];
ll inv[5005];
ll DP[5005][5005] , sum[5005][5005];
//DP[i][j] = p of winning if the current last number is i and we have picked j elements

inline ll qpow(ll x , ll n){
    if(n <= 0)return 1;
    ll ret = qpow(x , n / 2);
    ret = ret * ret % MOD;
    if(n & 1)ret = ret * x % MOD;
    return ret;
}

int main(){
    scanf("%d" , &N);
    for(int i = 1; i <= N; ++i){
        scanf("%d" , &a[i]);
        ++cnt[a[i]];
    }
    for(int i = 1; i <= N; ++i)inv[i] = qpow(i , MOD - 2);
    for(int j = N - 1; j >= 0; --j){
        for(int i = N; i >= 0; --i){
            if(cnt[i] > 1)DP[i][j] += cnt[i] - 1;
            if(DP[i][j] >= MOD)DP[i][j] -= MOD;
            if(DP[i][j] < 0)DP[i][j] += MOD;
            /*for(int k = i + 1; k <= N; ++k){
                DP[i][j] += DP[k][j + 1] * cnt[k] % MOD;
                if(DP[i][j] >= MOD)DP[i][j] -= MOD;
            }*/
            DP[i][j] = (DP[i][j] + sum[i + 1][j + 1] + MOD) % MOD;
            DP[i][j] *= inv[N - j];
            DP[i][j] %= MOD;
            sum[i][j] = (sum[i][j] + sum[i + 1][j] + DP[i][j] * cnt[i] % MOD) % MOD;
        }
    }    
    printf("%lld\n" , DP[0][0]);
}