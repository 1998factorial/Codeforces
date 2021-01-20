#pragma GCC optimize(3)
#pragma GCC optimize("Ofast")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")
#pragma comment(linker, "/stack:200000000")
#include <bits/stdc++.h>
#define sz(a) a.size()
using namespace std;
typedef long long ll;
const int mod = 998244353;
const int maxn = 1e5 + 10;
int fac[maxn * 2] , inv[maxn * 2] , N , LEN[maxn * 2];

inline int C(int n , int r){
    if(n < r || n < 0 || r < 0)return 0;
    return (ll)fac[n] * ((ll)inv[n - r] * inv[r] % mod) % mod;
}

inline ll qpow(int x , int n){
    ll ret = 1;
    while(n){
        if(n % 2)ret = (ll)ret * x % mod;
        x = (ll)x * x % mod;
        n >>= 1;
    }
    return (ret % mod + mod) % mod;
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

void change(vector<int>& y , int len) {
    int i, j, k;
    for (i = 1, j = len / 2; i < len - 1; i++) {
        if (i < j) swap(y[i], y[j]);
        k = len / 2;
        while (j >= k) {
            j = j - k;
            k = k / 2;
        }
        if (j < k) j += k;
    }
}

void NTT(vector<int>& P , int op){
    int len = sz(P) , i , j , k;
    //change(P , len);

    for(int i = 1, j = 0; i < len - 1; ++i) {
		for(int k = len >> 1; (j ^= k) < k; k >>= 1);
		if(i < j) swap(P[i], P[j]);
	}

    for(i = 1; i < len; i <<= 1){
        int gn = qpow(3 , (mod - 1) / (i << 1));
        if(op == -1)gn = qpow(gn , mod - 2);
        for(j = 0; j < len; j += (i << 1)){
            int g = 1;
            for(k = 0; k < i; ++k , g = mul(g , gn)){
                int x = P[j + k] , y = mul(g , P[j + k + i]);
                P[j + k] = add(x , y);
                P[j + k + i] = sub(x , y);
            }
        }
    }
    if(op == -1){
        //int inv = qpow(len , mod - 2);
        for(i = 0; i < len; ++i)P[i] = mul(P[i] , LEN[len]);
    }
}

vector<int> multiply(vector<int> a , vector<int> b){
    int n = sz(a) , m = sz(b) , len = 1 , i;
    while(len < n + m)len <<= 1;
    a.resize(len) , b.resize(len);
    NTT(a , 1);
    NTT(b , 1);
    for(i = 0; i < len; ++i)a[i] = mul(a[i] , b[i]);
    NTT(a , -1);
    a.resize(n + m);
    return a;
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
        ans2 = multiply(F , ans);
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