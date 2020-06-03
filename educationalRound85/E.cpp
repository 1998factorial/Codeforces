/*
    Math , Observation , Greedy

    D is at most 10 ^ 15, so it make sense to consider it's prime factorisation form
    when we travel from x to y, each time, we either get rid of one prime or we pick up one prime
    Claim: all shortest path from x to y must go through gcd(x , y)

    we only need to figure out how many ways are there for x to go to gcd(x , y)
    in another word, we need the number of ways to make x / gcd(x , y) to 1 by removing
    a prime number each time

    ans = #(reduce x / gcd(x , y) to 1) * #(reduce y / gcd(x , y) to 1)
*/
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const ll mod = 998244353;
const int maxn = 1e5 + 10;
ll fac[maxn] , ifac[maxn];

ll qpow(ll x , ll n){
    if(n <= 0)return 1ll;
    ll ret = qpow(x , n >> 1);
    ret = ret * ret % mod;
    if(n & 1)ret = ret * x % mod;
    return ret;
}

ll gcd(ll a , ll b){
    return a == 0 ? b : gcd(b % a , a);
}

int main(){
    ll D; scanf("%lld" , &D);
    int q; scanf("%d" , &q);
    // factorise D
    vector<ll> factors;
    ll M = D;
    for(ll p = 2ll; p * p <= D; ++p){
        if(M % p == 0){
            factors.push_back(p);
            while(M % p == 0){
                M /= p;
            }
        }
    }
    if(M > 1)factors.push_back(M);
    fac[0] = 1; ifac[0] = qpow(fac[0] , mod - 2);
    for(int i = 1; i < maxn; ++i){
        fac[i] = fac[i - 1] * i % mod;
        ifac[i] = qpow(fac[i] , mod - 2);
    }
    while(q--){
        ll x , y; scanf("%lld %lld" , &x , &y);
        ll d = gcd(x , y);
        x /= d;
        y /= d;
        vector<int> a , b;
        for(ll i : factors){
            ll cnt1 = 0 , cnt2 = 0;
            while(x % i == 0){
                ++cnt1; x /= i;
            }
            while(y % i == 0){
                ++cnt2; y /= i;
            }
            if(cnt1)a.push_back(cnt1);
            if(cnt2)b.push_back(cnt2);
        }
        ll ret = 1;
        int s1 = 0 , s2 = 0;
        for(int i : a)s1 += i , ret = ret * ifac[i] % mod;
        for(int i : b)s2 += i , ret = ret * ifac[i] % mod;
        ret = ret * fac[s1] % mod;
        ret = ret * fac[s2] % mod;
        printf("%lld\n" , ret);
    }
}
