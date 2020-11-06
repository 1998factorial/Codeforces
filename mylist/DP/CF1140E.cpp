#include <bits/stdc++.h>
#define MOD 998244353
using namespace std;
typedef long long ll;
const int maxn = 2e5 + 10;
int N , K , a[maxn];
ll DP[maxn][2]; 
// DP[i][j] = # of ways to put in a,-1,-1...,-1,b , i (-1)s, st a[i] != a[i + 2] for all i
// a,-1,-1...-1,b  0 -> a != b , 1 -> a = b

// even
// DP[i][0] = DP[i - 1][1] + (K - 2) * DP[i - 1][0]
// DP[i][1] = (K - 1) * DP[i - 1][0]
// odd 
// DP[i][0] = DP[i / 2][0] * DP[i / 2][1] * 2 + (K - 2) * DP[i / 2][0] * DP[i / 2][0]
// DP[i][1] = DP[i / 2][1] * DP[i / 2][1] + (K - 1) * DP[i / 2][0] * DP[i / 2][0]

// OR we can just ignore even and odd stuff...

ll solve(vector<int>& vec){
    int sz = vec.size();
    int cnt = 0;
    for(int i = 0; i < sz; ++i)cnt += vec[i] == -1;
    if(cnt == sz){
        ll ret = K;
        for(int i = 1; i < sz; ++i)ret *= K - 1 , ret %= MOD;
        return ret;
    }
    ll ret = 1;
    int i = 0;
    while(i < sz && vec[i] == -1)ret *= K - 1 , ret %= MOD , ++i;
    while(sz > i && vec[sz - 1] == -1)ret *= K - 1 , ret %= MOD , --sz;
    int pre = i; ++i;
    for(; i < sz; ++i){
        if(vec[i] == -1)continue;
        int len = i - pre + 1;
        len -= 2;
        ret *= DP[len][vec[i] == vec[pre]];
        ret %= MOD;
        pre = i;
    }
    return ret;
}

int main(){
    scanf("%d%d" , &N , &K);
    vector<int> even , odd;
    for(int i = 1; i <= N; ++i){
        scanf("%d" , &a[i]);
        if(i & 1)odd.push_back(a[i]);
        else even.push_back(a[i]);
    }
    DP[0][0] = 1;
    for(int i = 1; i <= N; ++i){
        /*if(i & 1){
            DP[i][0] = (DP[i / 2][0] * DP[i / 2][1] % MOD * 2 % MOD + (K - 2) * DP[i / 2][0] % MOD * DP[i / 2][0] % MOD) % MOD;
            DP[i][1] = (DP[i / 2][1] * DP[i / 2][1] % MOD + (K - 1) * DP[i / 2][0] % MOD * DP[i / 2][0] % MOD) % MOD;
        }
        else{
            DP[i][0] = (DP[i - 1][1] + (K - 2) * DP[i - 1][0] % MOD) % MOD;
            DP[i][1] = (K - 1) * DP[i - 1][0] % MOD;
        }*/
        DP[i][0] = (DP[i - 1][1] + (K - 2) * DP[i - 1][0] % MOD) % MOD;
        DP[i][1] = (K - 1) * DP[i - 1][0] % MOD;
        //for(int j : {0 , 1})printf("DP[%d][%d] = %lld\n " , i , j , DP[i][j]);
    }
    ll ans = 1;
    ans *= solve(even);
    ans %= MOD;
    ans *= solve(odd);
    ans %= MOD;
    printf("%lld\n" , ans);
}