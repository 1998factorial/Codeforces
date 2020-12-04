#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll MOD = 998244353;
const int maxn = 2e5 + 10;
ll DP[maxn] , p[maxn] , sum[maxn][2];

inline ll qpow(ll x , ll n){
    if(n <= 0)return 1;
    ll ret = qpow(x , n / 2);
    ret = ret * ret % MOD;
    if(n & 1)ret = ret * x % MOD;
    return ret;
}

int main(){
    int N;
    cin >> N;
    p[0] = 1;
    for(int i = 1; i < maxn; ++i)p[i] = p[i - 1] * 2 % MOD;
    DP[0] = 1;
    sum[0][0] = 1;
    sum[0][1] = 0;
    for(int i = 1; i <= N; ++i){
        int k = (i - 1) / 2;
        //for(int k = 0; k <= (i - 1) / 2; ++k){
        //    DP[i] += DP[i - 2 * k - 1];
        //    if(DP[i] >= MOD)DP[i] -= MOD;
        //}
        int pt = i & 1;
        DP[i] = sum[i - 1][1 - pt] - (i - 2 * k - 2 >= 0 ? sum[i - 2 * k - 2][1 - pt] : 0);
        if(DP[i] < 0)DP[i] += MOD;
        for(int j = 0; j < 2; ++j)sum[i][j] = sum[i - 1][j];
        sum[i][i & 1] += DP[i];
        if(sum[i][i & 1] >= MOD)sum[i][i & 1] -= MOD;
    }
    cout << DP[N] * qpow(p[N] , MOD - 2) % MOD << endl;
}