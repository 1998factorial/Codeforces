#include <bits/stdc++.h>
#define x first
#define y second
using namespace std;
typedef long long ll;
const ll MOD = 1e9 + 7;
ll N , K , DP[100][10005] , inv[100];
map<ll , int> fcnt;

inline ll qpow(ll x , ll n){
    if(n <= 0)return 1;
    ll ret = qpow(x , n / 2);
    ret = ret * ret % MOD;
    if(n & 1)ret = ret * x % MOD;
    return ret;
}

ll solve(int M , ll p){
    memset(DP , 0 , sizeof(DP));
    // DP[i][j] = probability when we have done j steps, ending with p^i
    DP[M][0] = 1;
    for(int j = 1; j <= K; ++j){
        for(int i = 0; i <= M; ++i){
            for(int k = i; k <= M; ++k){
                DP[i][j] += DP[k][j - 1] * inv[k + 1] % MOD;
                if(DP[i][j] >= MOD)DP[i][j] -= MOD;
            }
        }
    }
    ll ret = 0 , np = 1;
    for(int i = 0; i <= M; ++i , np *= p , np %= MOD){
        ret += DP[i][K] * np % MOD;
        if(ret >= MOD)ret -= MOD;
    }
    return ret;
}

int main(){
    cin >> N >> K;
    for(int i = 0; i < 100; ++i)inv[i] = qpow(i , MOD - 2);
    for(ll i = 2; i * i <= N; ++i){
        if(N % i == 0){
            while(N % i == 0){
                ++fcnt[i];
                N /= i;
            }
        }
    }
    if(N > 1)++fcnt[N];
    ll ret = 1;
    for(auto& e : fcnt){
        ret *= solve(e.y , e.x);
        ret %= MOD;
    }
    cout << ret << endl;
}