#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll MOD = 1e9 + 7;
ll N , M , inv;

ll qpow(ll x , ll n){
    if(n <= 0)return 1;
    ll ret = qpow(x , n / 2);
    ret = ret * ret % MOD;
    if(n & 1)ret = ret * x % MOD;
    return ret;
}

ll sum(ll n){
    return ((n % MOD) * ((n + 1) % MOD) % MOD) * inv % MOD;
}

int main(){
    scanf("%lld %lld" , &N , &M);
    inv = qpow(2ll , MOD - 2);
    ll ret = (N % MOD) * (M % MOD) % MOD;
    M = min(M , N);
    ll minv = M;
    // split the sum into 2 parts
    // part1 : v in [1 , sqrt(N)]
    // part2 : N / i <= sqrt(N)
    for(ll v = 1; v * v <= N; ++v){
        ll L = N / (v + 1) , R = N / v;
        R = min(R , M);
        if(L >= R)continue;
        minv = L;
        ll val = (sum(R) - sum(L) + MOD) % MOD;
        val = val * v % MOD;
        ret -= val;
        ret += MOD;
        ret %= MOD;
    }
    for(ll i = 1; i <= minv; ++i){
        ret -= (N / i % MOD) * i % MOD; 
        ret += MOD;
        ret %= MOD;
    }
    printf("%lld\n" , ret);
}   