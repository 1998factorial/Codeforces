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

ll f(int sz){ // frequency of a set size = sz where w[1] is in
    ll ret = C(N - 1 , sz - 1);
    // left (K - 1) groups , with N - X ppl
    // each ppl has K - 1 choice , so total = (K - 1) ^ (N - X)
    // but no group should be left empty
    if(K == 1 && N - sz)return 0;
    if(K > 1){
        ret *= C(N - sz - 1 , K - 2);
        ret %= mod;
    }
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
    for(sz = 1; sz <= N - K + 1; ++sz){
        ll v = f(sz);
        v *= sz;
        v %= mod;
        acc += v;
        acc %= mod;
    }
    ans *= acc;
    ans %= mod;
    printf("%lld\n" , (ans % mod + mod) % mod);
}