#include <bits/stdc++.h>
#define rep(i , a , b) for(int i = a; i <= b; ++i)
#define rrep(i , a , b) for(int i = a; i >= b; --i)
using namespace std;
typedef long long ll;
const int MOD = 1e9 + 7;
ll DP[5005][5005];
ll inline qpow(ll x , ll n){
    if(n <= 0)return 1;
    ll ret = qpow(x , n / 2);
    ret = ret * ret % MOD;
    if(n & 1)ret = ret * x % MOD;
    return ret;
}
// x^a * (1+x)^b
ll solve(int k , int a , int tot){
    if(~DP[k][a]){
        return DP[k][a];
    }
    int b = tot - a;
    if(k == 0){
        DP[k][a] = qpow(2ll , b);
        return DP[k][a];
    }
    ll& ret = DP[k][a];
    ret = 0;
    ret += solve(k - 1 , a , tot) * a % MOD;
    if(ret >= MOD)ret -= MOD;
    if(b)ret += solve(k - 1 , a + 1 , tot) * b % MOD;
    if(ret >= MOD)ret -= MOD;
    return ret;
}

int N , K;
int main(){
    cin >> N >> K;
    rep(i , 0 , K){
        rep(j , 0 , K){
            DP[i][j] = -1;
        }
    }
    cout << solve(K , 0 , N) << endl;
}