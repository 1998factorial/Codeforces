#include <bits/stdc++.h>
#define MOD 998244353
using namespace std;
typedef long long ll;

int H , W , N;
int r[3650] , c[3650];
ll rway[3650][3650] , cway[3650][3650];
ll fac[3650] , ifac[3650];

ll qpow(ll x , ll n){
    if(n <= 0)return 1;
    ll ret = qpow(x , n / 2);
    ret = ret * ret % MOD;
    if(n & 1)ret = ret * x % MOD;
    return ret;
}

void init(){
    fac[0] = 1; ifac[0] = qpow(fac[0] , MOD - 2);
    for(int i = 1; i < 3650; ++i){
        fac[i] = fac[i - 1] * i % MOD;
        ifac[i] = qpow(fac[i] , MOD - 2);
    }
}

ll C(int n , int r){
    if(n < 0 || r < 0 || n < r)return 0;
    return fac[n] * (ifac[r] * ifac[n - r] % MOD) % MOD;
}

int main(){
    init();
    scanf("%d%d%d" , &H , &W , &N);
    for(int i = 1; i <= N; ++i){
        int r1 , c1 , r2 , c2;
        scanf("%d%d%d%d" , &r1 , &c1 , &r2 , &c2);
        ++r[r1]; ++r[r2]; ++c[c1]; ++c[c2];
    }
    int dh = 0 , dw = 0;
    for(int i = 1; i <= H; ++i)dh += r[i] != 0;
    for(int i = 1; i <= W; ++i)dw += c[i] != 0;
    // solve for rways
    rway[0][0] = 1;
    for(int i = 1; i <= H; ++i){
        for(int j = 0; j <= i; ++j){
            rway[i][j] += rway[i - 1][j];
            if(rway[i][j] >= MOD)rway[i][j] -= MOD;
            if(j > 0 && i - 1 > 0 && !r[i] && !r[i - 1])rway[i][j] += rway[i - 2][j - 1];
            if(rway[i][j] >= MOD)rway[i][j] -= MOD;
        }
    }
    // solve for cways
    cway[0][0] = 1;
    for(int i = 1; i <= W; ++i){
        for(int j = 0; j <= i; ++j){
            cway[i][j] += cway[i - 1][j];
            if(cway[i][j] >= MOD)cway[i][j] -= MOD;
            if(j > 0 && i - 1 > 0 && !c[i] && !c[i - 1])cway[i][j] += cway[i - 2][j - 1];
            if(cway[i][j] >= MOD)cway[i][j] -= MOD;
        }
    }
    ll ret = 0;
    for(int nv = 0; nv <= H; ++nv){
        for(int nh = 0; nh <= W; ++nh){
            ll v = 1;
            v *= rway[H][nv] * C(H - 2 * nv - dh , nh) % MOD;
            v %= MOD;
            v *= cway[W][nh] * C(W - 2 * nh - dw , nv) % MOD;
            v %= MOD;
            v *= fac[nh];
            v %= MOD;
            v *= fac[nv];
            v %= MOD;
            ret += v;
            if(ret >= MOD)ret -= MOD;
        }
    }
    printf("%lld\n" , ret);
}