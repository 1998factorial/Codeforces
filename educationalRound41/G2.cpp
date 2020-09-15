#include <bits/stdc++.h>
#define ID if(0)
using namespace std;
typedef long long ll;

const int maxn = 2e5 + 10;
const ll mod = 1e9 + 7;
ll fac[maxn] , ifac[maxn];
int N , K;
ll w[maxn];
inline ll qpow(ll x , ll n){
    ll ret = 1;
    while(n){
        if(n & 1)ret = ret * x % mod;
        x = x * x % mod;
        n >>= 1;
    }
    return ret;
}

ll C(int n , int r){
    if(n < 0 || r < 0 || n < r)return 0;
    return fac[n] * (ifac[r] * ifac[n - r] % mod) % mod;
}

ll S(int n , int k){ // calculate stirling number of the second kind
    ll ret = 0;
    for(int i = 0 , sign = 1; i <= k; ++i , sign *= -1){
        ret += (ll)sign * C(k , i) * qpow(k - i , n) % mod;
        ret = (ret + mod) % mod;
    }
    ret *= ifac[k];
    ret = (ret % mod + mod) % mod;
    return ret;
}

int main(){
    int i , sz;
    ll ans = 0;
    scanf("%d %d" , &N , &K);
    fac[0] = 1; ifac[0] = qpow(fac[0] , mod - 2);
    for(i = 1; i < maxn; ++i){
        fac[i] = fac[i - 1] * i % mod;
        ifac[i] = qpow(fac[i] , mod - 2);
    }
    for(i = 1; i <= N; ++i)scanf("%lld" , &w[i]) , ans += w[i] , ans %= mod;
    ll acc = 0;
    acc += S(N , K);
    acc %= mod;
    acc += S(N - 1 , K) * (N - 1) % mod;
    acc %= mod;
    ans *= acc;
    ans %= mod;
    printf("%lld\n" , (ans % mod + mod) % mod);
}