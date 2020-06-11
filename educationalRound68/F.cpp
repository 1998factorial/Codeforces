/*
    Probability and expected value (with yanghui's triangle optimization) rating 2400

    let P[i] be the probability that we can complete task i.
    the expected number of tasks that we can complete is:
    E = P[1] * X[1] + P[2] * X[2] + ... + P[N] * X[N]
    where random variable X[i] = 1 if we do task i, 0 if we did not do it
    thus, answer = P[1] + P[2] + ... + P[N]
    if t[1] + .. + t[i] + i <= T , P[i] = 1
    if t[1] + .. + t[i] > T , P[i] = 0
    otherwise , let K be max(i , T - (t[1] + .. + t[i])) , where K is largest number of
    delay we can have without going over T. Then P[i] = (C(i , 0) + C(i , 1) + ... + C(i , K)) * (1 / 2) ^ i
    Note that in order to calculate each P[i] for all i = 1 ... N , time complexity will be O(N * N) -> 4 * 10 ^ 10
    Now , we use yanghui's triangle to optimze this summation.
    C(N + 1 , x + 1) = C(N , x + 1) + C(N , x)
    therefore, sum{C(N + 1 , i) , 0 <= i <= x + 1} = 2 * sum{C(N , i) , 0 <= i <= x + 1} - C(N , x + 1)
    and we notice that K[i] will not go over too much and it will be monotonically decreasing after
    some i, so it suffices to use a prefix sum to keep track with it.
*/
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const ll mod = 1e9 + 7;
const int maxn = 2e5 + 10;

ll fac[maxn] , ifac[maxn] , p[maxn] , ip[maxn];
ll t[maxn];
int N;
ll T;

ll qpow(ll x , ll n){
    if(n <= 0)return 1;
    ll ret = qpow(x , n >> 1);
    ret = ret * ret % mod;
    if(n & 1)ret = ret * x % mod;
    return ret;
}

ll C(ll n , ll r){
    if(r > n || n < 0 || r < 0)return 0;
    return fac[n] * (ifac[r] * ifac[n - r] % mod) % mod;
}

void init(){
    fac[0] = p[0] = 1;
    ifac[0] = qpow(fac[0] , mod - 2);
    ip[0] = qpow(p[0] , mod - 2);
    for(int i = 1; i < maxn; ++i){
        fac[i] = fac[i - 1] * i % mod;
        p[i] = p[i - 1] * 2 % mod;
        ifac[i] = qpow(fac[i] , mod - 2);
        ip[i] = qpow(p[i] , mod - 2);
    }
}

int main(){
    init();
    scanf("%d %lld" , &N , &T);
    for(int i = 1; i <= N; ++i){
        scanf("%lld" , &t[i]);
    }
    ll sum = 0 , ret = 0 , prefix = 0;
    int pre = -1;
    for(int i = 1; i <= N; ++i){
        sum += t[i];
        if(sum > T)break;
        if(sum + i <= T){
            ret = (ret + 1) % mod;
            continue;
        }
        int K = min((ll)i , T - sum);
        if(prefix == 0){
            for(int j = 0; j <= K; ++j){
                prefix = (prefix + C(i , j)) % mod;
            }
            pre = K;
            ret = (ret + prefix * ip[i] % mod) % mod;
        }
        else{
            prefix = prefix * 2 % mod;
            prefix = (prefix - C(i - 1 , pre) + mod) % mod;
            while(pre > K){
                prefix = (prefix - C(i , pre) + mod) % mod;
                --pre;
            }
            ret = (ret + prefix * ip[i] % mod) % mod;
        }
    }
    printf("%lld\n" , ret);
}
