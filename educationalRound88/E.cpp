/*
    Counting , math , rating 2000
    as long as the minimal element in the sequence is divisible by all other elements in the
    sequence , then this sequence will be stable
*/
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int maxn = 5e5 + 10;
const ll mod = 998244353;
int N , K;
ll fac[maxn] , ifac[maxn];

ll qpow(ll x , int n){
    if(n <= 0)return 1;
    ll ret = qpow(x , n >> 1);
    ret = ret * ret % mod;
    if(n & 1)ret = ret * x % mod;
    return ret;
}

ll C(int n , int r){
    return fac[n] * (ifac[r] * ifac[n - r] % mod) % mod;
}

int main(){
    cin >> N >> K;
    fac[0] = 1; for(int i = 1; i <= N; ++i){
        fac[i] = fac[i - 1] * i % mod;
        ifac[i] = qpow(fac[i] , mod - 2);
    }
    ifac[0] = qpow(fac[0] , mod - 2);
    ll ret = 0;
    for(int i = 1; i <= N; ++i){
        ll cnt = (N - i) / i;
        if(cnt >= K - 1){
            ret += C(cnt , K - 1);
            ret %= mod;
        }
    }
    cout << ret << endl;
}
