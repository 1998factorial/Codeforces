#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const ll mod = 998244353;
const int maxn = 2e5 + 10;

ll fac[maxn] , ifac[maxn] , po[maxn];
ll N , M;

ll qpow(ll x , ll n ){
    if(n <= 0)return 1;
    ll ret = qpow(x , n >> 1);
    ret = ret * ret % mod;
    if(n & 1)ret = ret * x % mod;
    return ret;
}

ll C(int n , int r){
    return fac[n] * (ifac[n - r] * ifac[r] % mod) % mod;
}

int main(){
    cin >> N >> M;
    if(N == 2){
        cout << 0 << endl;
    }
    else{
        fac[0] = 1;
        po[0] = 1;
        ifac[0] = qpow(fac[0] , mod - 2);
        for(int i = 1; i < maxn; ++i){
            po[i] = po[i - 1] * 2 % mod;
            fac[i] = fac[i - 1] * i % mod;
            ifac[i] = qpow(fac[i] , mod - 2);
        }
        ll ret = N - 2;
        ret = ret * C(M , N - 1) % mod;
        ret = ret * po[N - 3] % mod;
        cout << ret << endl;
    }
}
