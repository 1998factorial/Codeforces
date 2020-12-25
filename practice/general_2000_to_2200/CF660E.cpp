#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int MOD = 1e9 + 7;
const int maxn = 1e6 + 10; // fix up
inline ll qpow(ll x , ll n){
    if(n <= 0)return 1;
    ll ret = qpow(x , n / 2);
    ret = ret * ret % MOD;
    if(n & 1)ret = ret * x % MOD;
    return ret;
}

int N , M;
ll f[maxn] , inv[maxn];

inline ll C(int n , int r){
    if(n < 0 || r < 0 || n < r)return 0;
    return f[n] * (inv[n - r] * inv[r] % MOD) % MOD;
}

void add(ll& x , ll y){
    x += y;
    if(x >= MOD)x -= MOD;
}

int main(){
    cin >> N >> M;
    f[0] = 1;
    inv[0] = qpow(f[0] , MOD - 2);
    for(int i = 1; i < maxn; ++i)f[i] = f[i - 1] * i % MOD , inv[i] = qpow(f[i] , MOD - 2);
    ll ret = qpow(M , N);
    // count, for each sequences' contribution
    // we don't want to overcount, so we always count the 
    // first occurence of such sequence

    /*for(int i = 1; i <= N; ++i){
        for(int j = 0; j <= N - i; ++j){
            ll v = C(N - j - 1 , i - 1) * qpow(M - 1 , N - i - j) % MOD;
            v = v * qpow(M , i + j) % MOD;
            add(ret , v);
        }
    }*/
    // the above can be transformed to below
    // 
    for(int s = 1; s <= N; ++s){
        ll v = qpow(M - 1 , N - s) * qpow(M , s) % MOD;
        v = v * C(N , s - 1) % MOD;
        add(ret , v);
    }
    cout << ret << endl;
}   