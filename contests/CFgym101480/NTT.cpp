#include <bits/stdc++.h>
#define ID if(0)
using namespace std;
typedef long long ll;
const int mod = 1009;
const int maxn = 2e5 + 10;
int N , M , K;
int cnt[maxn];
vector<vector<ll>> poly;

namespace Polynomial_NTT {
    // we use 998244353 and 1004535809
    using ll = long long;
    int g = 3, P = 998244353;
    constexpr int MXLEN = 1 << 20;
 
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

    class poly_t : public vector<ll> {
        public:
            poly_t() {}
            poly_t(initializer_list<ll> list) {
                for(const ll &val : list) push_back(val);
            }
            poly_t(const poly_t &A, ll size) {*this = A, resize(size);}
    };
 
    inline ll modAdd(ll u, ll v) {
        return (((u += v) >= P) && (u -= P)), u;
    }

    ll getInv(int u) {
        return u == 1 ? 1 : static_cast<ll>(P - P / u) * getInv(P % u) % P;
    }

    ll Pow(ll u, ll v) {
        ll ans = 1;
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
            for(ll &val : A)
                val = tmp * val % P;
        }
    }
 
    poly_t multiply(poly_t A, poly_t B) {
        static poly_t C;
        int X = 1, n = A.size(), m = B.size();
        for(; X < n + m; X <<= 1);
        C.resize(X);
        DFT(A, X, NORMAL), DFT(B, X, NORMAL);
        for(int i = 0; i < X; i++)
            C[i] = static_cast<ll>(A[i]) * B[i] % P;
        DFT(C, X, INVERSE), C.resize(n + m - 1);
        return C;
    }

} 
 
vector<ll> solve(int l , int r){
    if(l == r){
        vector<ll> ret(poly[l].size());
        for(int i = 0; i < poly[l].size(); ++i){
            ret[i] = poly[l][i];
        }
        return ret;
    }
    int mid = (l + r) >> 1;
    vector<ll> lp = solve(l , mid);
    vector<ll> rp = solve(mid + 1 , r);
    Polynomial_NTT::poly_t h , g;
    h.resize(lp.size()) , g.resize(rp.size());
    for(int i = 0; i < lp.size(); ++i)h[i] = lp[i];
    for(int i = 0; i < rp.size(); ++i)g[i] = rp[i];
    Polynomial_NTT::P = 998244353;
    Polynomial_NTT::poly_t r1 = Polynomial_NTT::multiply(h , g);
    Polynomial_NTT::P = 1004535809;
    Polynomial_NTT::poly_t r2 = Polynomial_NTT::multiply(h , g);
    vector<ll> ret(r1.size());
    for(int i = 0; i < r1.size(); ++i){
        ret[i] = ((Polynomial_NTT::mul(r1[i] , Polynomial_NTT::check[0]) + Polynomial_NTT::mul(r2[i] , Polynomial_NTT::check[1])) % Polynomial_NTT::MOD) % mod;
    }
    return ret;
}

int main(){
    int i , x , j;
    scanf("%d %d %d" , &N , &M , &K);
    for(i = 1; i <= N; ++i){
        int x; scanf("%d" , &x); ++cnt[x];
    }
    for(i = 1; i <= M; ++i){
        if(cnt[i] == 0)continue;
        vector<ll> pi(cnt[i] + 1 , 1);
        poly.push_back(pi);
    }
    vector<ll> ans = solve(0 , poly.size() - 1);
    printf("%lld\n" , ans[K]);
}