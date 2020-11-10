/*
    Combinatorics
    To force each cell to be under attack, either all rows/cols are captured by at least one rook.
    Assuming that we force each row has one rook, and we check the condition of exactly k pairs rooks
    attacking each other. The only way to make rooks attacking is to put them on the same column.
    if there are x rooks on the same column, then we created x - 1 pairs of attacking rooks.
    So, the goal is to distribute rooks, such that there are K pairs of rooks attacking.
    Notice that we need to first choose N - K columns and put one rook on each of them, then we can
    distribute the remaining K rooks on these N - K columns, guranteeing thawt there will be K pairs
    attacking. To count the number of ways of doing this, we can do: the total number of ways to
    distribute N rooks on N - K columns is (N - K) ^ N, we need to discard the configurations that
    there exists at least one column that has no rook on it. We can use inclusion-exclusion on this.
    # desired = # total - # at least one column has no rook + # at least 2 columns have no rook - ... +

    ans = C(N , N - K) * [(N - K) ^ N - C(N - K , 1) * (N - K - 1) ^ N + C(N - K , 2) * (N - K - 2) ... ]

    Need to times the ans by 2 if K > 0, by symmetry
    If K = 0, then we have all cols and rows are under attack by exactly one rook and there is no
    point to do the symmetry.
*/

#include <bits/stdc++.h>
#define MAXN 200005
using namespace std;
typedef long long ll;

ll N , K;
const ll mod = 998244353;
ll fac[MAXN] , ifac[MAXN];

ll qpow(ll x , ll n){
    if(n <= 0)return 1;
    ll ret = qpow(x , n >> 1);
    ret = ret * ret % mod;
    if(n & 1ll)ret = ret * x % mod;
    return ret;
}

ll C(ll n , ll r){
    return (fac[n] * ifac[n - r] % mod) * ifac[r] % mod;
}

int main(){
    scanf("%lld %lld" , &N , &K);
    if(K > N - 1){
        printf("0\n");
        return 0;
    }
    fac[0] = 1;
    ifac[0] = qpow(fac[0] , mod - 2);
    for(int i = 1; i < MAXN; ++i){
        fac[i] = fac[i - 1] * i % mod;
        ifac[i] = qpow(fac[i] , mod - 2);
    }
    ll ret = 0;
    for(int i = 0; i <= N - K; ++i){
        ll val = C(N - K , i) * qpow(N - K - i , N) % mod;
        if((i & 1) == 0){
            ret = (ret + val) % mod;
        }
        else{
            ret = (ret - val + mod) % mod;
        }
    }
    ret = ret * C(N , N - K) % mod;
    if(K > 0){
        ret = ret * 2ll % mod;
    }
    printf("%lld\n" , ret % mod);
}
