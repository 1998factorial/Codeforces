#pragma GCC optimize(3)
#pragma GCC optimize("Ofast")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")
#pragma comment(linker, "/stack:200000000")
#include <bits/stdc++.h>
#define sz(a) a.size()
using namespace std;
typedef long long ll;
typedef vector<int> vi;
const int mod = 998244353;
const int g = 3;
const int maxn = 1e5 + 10;
int fac[maxn * 2] , inv[maxn * 2] , N , LEN[maxn * 2];

inline int C(int n , int r){
    if(n < r || n < 0 || r < 0)return 0;
    return (ll)fac[n] * ((ll)inv[n - r] * inv[r] % mod) % mod;
}

inline ll qpow(ll b , ll p){
    ll res = 1;
	if (p < 0) p += mod - 1;
	while (p) {
		if (p & 1) (res *= b) %= mod;
		(b *= b) %= mod;
		p /= 2;
	}
	return res;
}

inline int add(int x , int y){
    int ret = x + y;
    if(ret > mod)ret -= mod;
    return ret;
}

inline int sub(int x , int y){
    int ret = x - y;
    if(ret < 0)ret += mod;
    return ret;
}

inline int mul(int x , int y){
    ll ret = (ll)x * y % mod;
    return ret;
}

int nearestPowerOfTwo (int n) {
	int ans = 1;
	while (ans < n) ans <<= 1;
	return ans;
}
 
void ntt (vector<int> &X, int inv) {
	int n = X.size();
	
	for (int i = 1, j = 0; i < n - 1; ++i) {
		for (int k = n >> 1; (j ^= k) < k; k >>= 1);
		if(i < j) swap(X[i], X[j]);
	}
	
	vector<ll> wp(n >> 1, 1);
	for (int k = 1; k < n; k <<= 1) {
		ll wk = qpow(g, inv * (mod - 1) / (k << 1));
		
		for (int j = 1; j < k; ++j)
			wp[j] = wp[j - 1] * wk % mod;
		
		for (int i = 0; i < n; i += k << 1) {
			for (int j = 0; j < k; ++j) {
				int u = X[i + j], v = X[i + j + k] * wp[j] % mod;
				X[i + j] = u + v < mod ? u + v : u + v - mod;
				X[i + j + k] = u - v < 0 ? u - v + mod : u - v;
			}
		}
	}
	
	if (inv == -1) {
		ll nrev = qpow(n, mod - 2);
		for(int i = 0; i < n; ++i)
			X[i] = X[i] * nrev % mod;
	}
}
 
vector<int> convolution (vector<int> A, vector<int> B){
	int sz = A.size() + B.size() - 1;
	int size = nearestPowerOfTwo(sz);
	
	A.resize(size), B.resize(size);
	ntt(A, 1), ntt(B, 1);
	
	for(int i = 0; i < size; i++)
		A[i] = 1ll * A[i] * B[i] % mod;
	
	ntt(A, -1);
	A.resize(sz);
	
	return A;
}

int main(){
    scanf("%d" , &N);
    vector<int> a(N) , b(N);
    for(int i = 0; i < N; ++i){
        scanf("%d %d" , &a[i] , &b[i]);
    }
    fac[0] = 1;
    inv[0] = qpow(fac[0] , mod - 2);
    for(int i = 1; i < maxn * 2; ++i){
        fac[i] = (ll)fac[i - 1] * i % mod;
        inv[i] = qpow(fac[i] , mod - 2);
        LEN[i] = qpow(i , mod - 2);
    }
    vector<int> ans(1 , 1);
    for(int i = 0; i < N; ++i){
        int M = sz(ans);
        int from = max(0 , b[i] - M + 1);
        int to = min(a[i] + b[i] , M + a[i] - 1);
        vector<int> ans2 , F(to - from + 1);
        for(int j = 0; j <= to - from; ++j){
            F[j] = C(a[i] + b[i] , from + j);
        }
        ans2 = convolution(F , ans);
        ans.resize(M + a[i] - b[i]);
        for(int j = 0 , k = b[i] - from; j < M + a[i] - b[i]; ++j , ++k){
            // start from term = C(a[i] + b[i] , b[i])
            ans[j] = ans2[k];
        }
    }
    int ret = 0;
    for(auto& x : ans){
        ret = add(ret , x);
    }
    printf("%d\n" , ret);
}