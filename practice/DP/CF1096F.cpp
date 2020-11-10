#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int maxn = 2e5 + 10;
const ll mod = 998244353;
ll E[maxn];
int a[maxn];
int sum1[maxn << 2]; // known
int cneg[maxn];
int miss[maxn];
int sum2[maxn]; // unknown
int N;
inline ll qpow(ll x , ll n){
    ll ret = 1;
    while(n){
        if(n & 1)ret = ret * x % mod;
        x = x * x % mod;
        n >>= 1;
    }
    return ret;
}
inline ll INV(int x){
    return qpow(x , mod - 2);
}
void add(int sum[] , int pos , int val){
    while(pos <= N){
        sum[pos] += val;
        pos += (-pos) & pos;
    }
}
int get(int sum[] , int pos){
    int ret = 0;
    while(pos){
        ret += sum[pos];
        pos -= (-pos) & pos;
    }
    return ret;
}

int main(){
    scanf("%d" , &N);
    int i;
    for(i = 1; i <= N; ++i)miss[i] = 1;
    for(i = 1; i <= N; ++i){
        scanf("%d" , &a[i]);
        cneg[i] = cneg[i - 1] + (a[i] == -1);
        if(~a[i]){
            miss[a[i]] = 0;
        }
    }
    for(i = 1; i <= N; ++i){
        sum2[i] = sum2[i - 1] + miss[i];
    }
    for(i = 1; i <= cneg[N]; ++i){
        E[i] = (E[i - 1] + (i - 1) * INV(2) % mod) % mod;
    }
    ll lv = 0;
    for(i = 1; i <= N; ++i){
        if(~a[i]){
            ll v = (ll)cneg[i] * (sum2[N] - sum2[a[i]]) % mod;
            v *= INV(cneg[N]);
            v %= mod;
            v = (v + mod) % mod;
            lv += v;
            lv %= mod;
        }
    }
    ll rv = 0;
    for(i = N; i >= 1; --i){
        if(~a[i]){
            ll v = (ll)(cneg[N] - cneg[i]) * sum2[a[i]] % mod;
            v *= INV(cneg[N]);
            v %= mod;
            v = (v + mod) % mod;
            rv += v;
            rv %= mod;
        }
    }
    ll ip = 0;
    for(i = 1; i <= N; ++i){
        if(~a[i]){
            ip += get(sum1 , N) - get(sum1 , a[i]);
            add(sum1 , a[i] , 1);
        }
    }

    ll ret = 0;
    ret += E[cneg[N]];
    ret %= mod;
    ret += ip;
    ret %= mod;
    ret += lv;
    ret %= mod;
    ret += rv;
    ret %= mod;
    printf("%lld\n" , ret);
}