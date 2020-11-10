#include <bits/stdc++.h>
#define x first
#define y second
using namespace std;
typedef long long ll;
typedef pair<int , int> ii;
const ll mod = 998244353;
const int maxn = 3e5 + 10;
int ncover[maxn];
int L[maxn] , R[maxn];
int N , M;
int a[25] , b[25];
ll fac[maxn] , ifac[maxn];
ll ans[maxn][50];

inline ll qpow(ll x , ll n){
    ll ret = 1;
    while(n){
        if(n & 1)ret = 1ll * ret * x % mod;
        x = 1ll * x * x % mod;
        n >>= 1;
    }
    return ret;
}
ll C(int n , int r){
    if(n < 0 || r < 0 || r > n)return 0;
    return fac[n] * (ifac[n - r] * ifac[r] % mod) % mod;
}
int main(){
    int i , j;
    scanf("%d %d" , &N , &M);
    fac[0] = 1; ifac[0] = qpow(fac[0] , mod - 2);
    for(i = 1; i <= N; ++i){
        scanf("%d %d" , &L[i] , &R[i]); 
        ++ncover[L[i]]; 
        --ncover[R[i] + 1];
        fac[i] = fac[i - 1] * i % mod;
        ifac[i] = qpow(fac[i] , mod - 2);
    }
    for(i = 1; i <= N; ++i){
        ncover[i] += ncover[i - 1];
    }
    for(i = 0; i < M; ++i){
        scanf("%d %d" , &a[i] , &b[i]);
    }
    for(j = 0; j <= 2 * M; ++j){
        for(i = 1; i <= N; ++i){
            ans[i][j] = (ans[i - 1][j] + C(ncover[i] - j , i - j)) % mod;
        }
    }
    ll ret = 0;
    for(i = 0; i < (1 << M); ++i){
        int l = 1 , r = N;
        set<int> vis;
        ll sign = (__builtin_popcount(i) % 2) ? -1 : 1;
        for(j = 0; j < M; ++j){
            if((1 << j) & i){
                vis.insert(a[j]);
                vis.insert(b[j]);
            }
        }
        for(int x : vis){
            l = max(l , L[x]);
            r = min(r , R[x]);
        }
        if(l > r)continue;
        ll val = (ans[r][vis.size()] - ans[l - 1][vis.size()]) % mod;
        val *= sign;
        val %= mod;
        ret += val;
        ret %= mod;
    }
    printf("%lld\n" , (ret % mod + mod) % mod);
}