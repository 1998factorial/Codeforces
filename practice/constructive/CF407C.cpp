#include <bits/stdc++.h>
#define ID if(0)
using namespace std;
typedef long long ll;
const int maxn = 1e5 + 1000;
const ll mod = 1e9 + 7;
int N , M , K;
ll a[105][maxn] , fac[maxn] , inv[maxn] , sum[105][maxn];

ll qpow(ll x , ll n){
    ll ret = 1;
    while(n){
        if(n & 1) ret = (ret * x) % mod;
        x = (x * x) % mod;
        n >>= 1;
    }
    return ret;
}

ll C(int n , int r){
    if(n < r || n < 0 || r < 0)return 0;
    return fac[n] * (inv[n - r] * inv[r] % mod) % mod;
}

void init(){
    fac[0] = 1;
    inv[0] = qpow(fac[0] , mod - 2);
    for(int i = 1; i < maxn; ++i){
        fac[i] = fac[i - 1] * i % mod;
        inv[i] = qpow(fac[i] , mod - 2);
    }
}

int main(){
    int i , j;
    init();
    scanf("%d %d" , &N , &M);
    for(i = 1; i <= N; ++i){
        scanf("%lld" , &a[0][i]);
    }
    for(i = 1; i <= M; ++i){
        int l , r , k;
        scanf("%d %d %d" , &l , &r , &k);
        a[k + 1][l] = (a[k + 1][l] + 1) % mod;
        ID printf("a[%d][%d] added by 1\n" , k + 1 , l);
        for(j = 1; j <= k + 1; ++j){
            a[j][r + 1] = (a[j][r + 1] - C(r - l + k + 1 - j , k + 1 - j) + mod) % mod;
            ID printf("a[%d][%d] is subtracted by C(%d , %d)\n" , j , r + 1 , r - l + k + 1 - j , k + 1 - j);
        }
    }
    for(j = 104; j >= 1; --j){
        for(i = 1; i <= N; ++i){
            a[j - 1][i] = (a[j - 1][i] + sum[j][i]) % mod;
        }
        for(i = 1; i <= N; ++i){
            sum[j - 1][i] = (sum[j - 1][i - 1] + a[j - 1][i]) % mod;
        }
    }
    for(i = 1; i <= N; ++i){
        printf("%lld " , a[0][i]);
    }
    printf("\n");
}