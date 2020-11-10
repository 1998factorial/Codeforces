#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll MOD = 1e9 + 7;
const int maxn = 1e5 + 10;
ll DP[maxn];
int M;

ll qpow(ll x , ll n){
    if(n <= 0)return 1;
    ll ret = qpow(x , n / 2);
    ret = ret * ret % MOD;
    if(n & 1)ret = ret * x % MOD;
    return ret;
}

ll gcd(ll x , ll y){
    return x == 0 ? y : gcd(y % x , x);
}

int main(){
    cin >> M;
    DP[1] = 1;
    ll inv = qpow(M , MOD - 2) , ans = 1;
    for(int i = 2; i <= M; ++i){
        int cnt = 0;
        DP[i] = 1;
        for(int j = 1; j <= M; ++j){
            int d = gcd(j , i);
            if(d == i){
                ++cnt;
            }
            else{
                DP[i] += DP[d] * inv % MOD;
                if(DP[i] >= MOD)DP[i] -= MOD;
            }
        }
        ll v = 1ll - inv * cnt % MOD;
        if(v < 0)v += MOD;
        DP[i] = DP[i] * qpow(v , MOD - 2) % MOD;
        ans += DP[i];
        if(ans >= MOD)ans -= MOD;
    }
    ans = ans * inv % MOD;
    cout << ans << endl;
}