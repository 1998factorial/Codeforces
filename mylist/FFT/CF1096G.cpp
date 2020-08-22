#include <bits/stdc++.h>
#define ID if(0)
using namespace std;
typedef long long ll;
const ll mod = 998244353;
const int maxn = 2e5 + 10;
inline ll qpow(ll x , ll n){
    ll ret = 1ll;
    while(n){
        if(n % 2)ret = ret * x % mod;
        x = x * x % mod;
        n >>= 1;
    }
    return ret;
}
vector<bool> D;
vector<vector<ll>> poly;
int N , K;

void change(vector<ll>& y , int len) {
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

void NTT(vector<ll>& P , int op){
    int len = P.size() , i , j , k;
    change(P , len);
    for(i = 1; i < len; i <<= 1){
        ll gn = qpow(3ll , (mod - 1) / (i << 1));
        if(op == -1)gn = qpow(gn , mod - 2);
        for(j = 0; j < len; j += (i << 1)){
            ll g = 1;
            for(k = 0; k < i; ++k , g = g * gn % mod){
                ll x = P[j + k] , y = g * P[j + k + i] % mod;
                P[j + k] = (x + y) % mod;
                P[j + k + i] = (x - y + mod) % mod;
            }
        }
    }
    if(op == -1){
        ll inv = qpow(len , mod - 2);
        for(i = 0; i < len; ++i)P[i] = P[i] * inv % mod;
    }
}

vector<ll> multiply(vector<ll> aa , vector<ll> bb){
    int n = aa.size() , m = bb.size() , len = 1 , i;
    while(len < n + m)len <<= 1;
    vector<ll> a(len) , b(len);
    for(i = 0; i < n; ++i)a[i] = aa[i];
    for(i = 0; i < m; ++i)b[i] = bb[i];
    NTT(a , 1);
    NTT(b , 1);
    vector<ll> c(len);
    for(i = 0; i < len; ++i)c[i] = a[i] * b[i] % mod;
    NTT(c , -1);
    while(!c.empty() && c.back() == 0)c.pop_back();
    return c;
}

vector<ll> solve(vector<ll>& v , int n){
    vector<ll> ret = {1};
    while(n){
        if(n & 1)ret = multiply(ret , v);
        v = multiply(v , v);
        n >>= 1;
    }
    return ret;
}

int main(){
    D = vector<bool> (10);
    poly = vector<vector<ll>> ();
    int i , j;
    scanf("%d %d" , &N , &K);
    for(i = 1; i <= K; ++i){
        int x; scanf("%d" , &x);
        D[x] = 1;
    }
    vector<ll> v;
    for(j = 0; j < 10; ++j){
        v.push_back(D[j]);
    }
    poly.push_back(v);
    vector<ll> first_half = solve(v , N / 2);
    ll ans = 0;
    for(ll x : first_half){
        ans += x * x % mod;
        ans %= mod;
    }
    printf("%lld\n" , (ans + mod) % mod);
}