#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll mod = 1e6 + 3;
const int maxn = 2e5 + 10;
int N , A , B , C;
ll l[maxn] , t[maxn] , fac[maxn * 2] , inv[maxn * 2];

// This is a NTT example, it computes the convolution of 
// 2 polynomials 1e6 + 3
// this template runs NTT twice with 2 different primes and restore
// result with a larger prime MOD

namespace Polynomial_NTT {
    // we use 998244353 and 1004535809
    using ll = long long;
    int g = 3, P = 998244353;
    constexpr int MXLEN = 1 << 19;
 
    const ll MOD = 1002772198720536577ll;
    const ll check[] = {334257240187163831ll, 668514958533372747ll};

    inline ll mul(ll a, ll b) { // multiply a with b, modules MOD = 1002772198720536577
        ll ans = 0;
        if(a < b) swap(a, b);
        while(b) {
            if(b & 1) ans = (ans + a) % MOD;
            a = a * 2 % MOD;
            b >>= 1;
        }
        return ans;
    }

    class poly_t : public vector<int> {
        public:
            poly_t() {}
            poly_t(initializer_list<int> list) {
                for(const int &val : list) push_back(val);
            }
            poly_t(const poly_t &A, int size) {*this = A, resize(size);}
    };
 
    inline int modAdd(int u, int v) {return (((u += v) >= P) && (u -= P)), u;}
    int getInv(int u) {
        return u == 1 ? 1 : static_cast<ll>(P - P / u) * getInv(P % u) % P;
    }
    int Pow(int u, int v) {
        int ans = 1;
        for(; v; v >>= 1, u = static_cast<ll>(u) * u % P)
            if(v & 1) ans = static_cast<ll>(u) * ans % P;
        return ans;
    }
 
    enum DFT_FLAG_t {NORMAL = 1, INVERSE = -1};
    void DFT(poly_t &A, int n, DFT_FLAG_t flag = NORMAL) {
        static int prevLen, rev[MXLEN + 1];
        if(prevLen != n) {
            prevLen = n;
            for(int i = 0; i < n; i++)
                rev[i] = (rev[i >> 1] >> 1) | ((i & 1) * (n >> 1));
        }
        if(static_cast<int>(A.size()) != n) A.resize(n);
 
        for(int i = 0; i < n; i++)
            if(i < rev[i]) swap(A[i], A[rev[i]]);
        for(int i = 1; i < n; i <<= 1) {
            ll wn = Pow(g, P - 1 + flag * (P - 1) / (i << 1));
            for(int j = 0; j < n; j += i << 1)
                for(int k = 0, w = 1; k < i; k++, w = wn * w % P) {
                    int x0 = A[j + k], x1 = static_cast<ll>(w) * A[i + j + k] % P;
                    A[j + k] = modAdd(x0, x1);
                    A[i + j + k] = modAdd(x0, P - x1);
                }
        }
        if(flag == INVERSE) {
            ll tmp = getInv(n);
            for(int &val : A)
                val = tmp * val % P;
        }
    }
 
    poly_t multiply(poly_t A, poly_t B) {
        static poly_t C;
        int X = 1, n = A.size(), m = B.size();
        for(; X < n + m - 1; X <<= 1);
        C.resize(X);
        DFT(A, X, NORMAL), DFT(B, X, NORMAL);
        for(int i = 0; i < X; i++)
            C[i] = static_cast<ll>(A[i]) * B[i] % P;
        DFT(C, X, INVERSE), C.resize(n + m - 1);
        return C;
    }

} 
Polynomial_NTT::poly_t h, g;

inline ll qpow(ll x , ll n){
    ll ret = 1ll;
    while(n){
        if(n % 2)ret = ret * x % mod;
        x = x * x % mod;
        n >>= 1;
    }
    return ret;
}

inline ll choose(int n , int r){
    if(n < r || n < 0 || r < 0)return 0;
    return fac[n] * (inv[n - r] * inv[r] % mod) % mod;
}

int main(){
    scanf("%d %d %d %d" , &N , &A , &B , &C);
    for(int i = 1; i <= N; ++i){
        scanf("%lld" , &l[i]);
    }
    for(int i = 1; i <= N; ++i){
        scanf("%lld" , &t[i]);
    }
    fac[0] = 1 , inv[0] = qpow(fac[0] , mod - 2);
    for(int i = 1; i < maxn * 2; ++i){
        fac[i] = fac[i - 1] * i % mod;
        inv[i] = qpow(fac[i] , mod - 2);
    }
    ll ans = 0;
    for(int i = 2; i <= N; ++i){
        // contribution of t[i] in F[N][N]
        ll v = qpow(A , N - i) * qpow(B , N - 1) % mod;
        v = v * t[i] % mod;
        v = v * choose(2 * N - 2 - i , N - i) % mod;
        ans += v;
        ans %= mod;
    }
    for(int i = 2; i <= N; ++i){
        // contribution of l[i] in F[N][N]
        ll v = qpow(A , N - 1) * qpow(B , N - i) % mod;
        v = v * l[i] % mod;
        v = v * choose(2 * N - 2 - i , N - i) % mod;
        ans += v;
        ans %= mod;
    }
    // calculate the coefficient of C in F[N][N]
    h.resize(N - 1); g.resize(N - 1);
    for(int i = 0; i <= N - 2; ++i){
        h[i] = qpow(A , i) * inv[i] % mod;
        g[i] = qpow(B , i) * inv[i] % mod;
    }
    // DO NTT twice for different primes
    Polynomial_NTT::P = 998244353;
    Polynomial_NTT::poly_t hg1 = Polynomial_NTT::multiply(h , g);
    Polynomial_NTT::P = 1004535809;
    Polynomial_NTT::poly_t hg2 = Polynomial_NTT::multiply(h , g);
    ll coe = 0;
    for(int i = 0; i <= 2 * N - 4; ++i){
        ll val = (Polynomial_NTT::mul(hg1[i] , Polynomial_NTT::check[0]) + Polynomial_NTT::mul(hg2[i] , Polynomial_NTT::check[1])) % Polynomial_NTT::MOD % mod;
        // restore (h * g)[i]
        coe += fac[i] * val % mod;
        coe %= mod;
    }
    coe = coe * C % mod;
    ans += coe;
    ans %= mod;
    printf("%lld\n" , ans);
}