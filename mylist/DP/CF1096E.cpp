#include <bits/stdc++.h>
#define ID if(1)
using namespace std;
typedef long long ll;
const ll mod = 998244353;
ll fac[10050];
ll ifac[10050];
int N , S , R;

inline ll qpow(ll x , ll n){
    ll ret = 1;
    while(n){
        if(n & 1)ret = ret * x % mod;
        x = x * x % mod;
        n >>= 1;
    }
    return ret;
}

ll inv(ll x){
    return qpow(x , mod - 2);
}

ll C(int n , int r){
    if(n == r)return 1;
    if(n < 0 || r < 0 || n < r)return 0;
    return fac[n] * (ifac[r] * ifac[n - r] % mod) % mod;
}

ll solve(int score , int ppl){
    // the probability that there are ppl + 1 (including a[1]) = score, and each of other N - j - 1 a[k] < i ?
    int Sn = S - (ppl + 1) * score; // score left
    int np = N - ppl - 1; // ppl left
    // inclusion - exclusion
    ll ret = 0;
    for(int i = 0 , sign = 1; i <= np; ++i , sign *= -1){
        ll v = C(Sn - i * score + np - 1 , np - 1) * C(np , i) % mod;
        v *= (~sign) ? 1 : mod - 1;
        v %= mod;
        ret += v;
        ret %= mod;
    }
    return ret % mod;
}

int main(){
    int i , j;
    scanf("%d %d %d" , &N , &S , &R);
    fac[0] = 1; ifac[0] = inv(fac[0]);
    for(i = 1; i <= 10005; ++i){
        fac[i] = fac[i - 1] * i % mod;
        ifac[i] = inv(fac[i]);
    }
    ll ret = 0;
    for(i = R; i <= S; ++i){
        for(j = 0; j <= N - 1; ++j){
            ll v = solve(i , j);
            v *= inv(j + 1);
            v %= mod;
            v *= C(N - 1 , j);
            v %= mod;
            ret += v;
            ret %= mod;
        }
    }
    ret *= inv(C(S - R + N - 1 , N - 1));
    ret %= mod;
    printf("%lld\n" , (ret % mod + mod) % mod);
}  