// the use of linarity of expectation 
#include <bits/stdc++.h>
#define ID if(0)
using namespace std;
typedef long long ll;
typedef pair<ll , ll> ii;
const ll mod = 998244353;
const int maxn = 2e5 + 10;
ll qpow(ll x , ll n){
    ll ret = 1;
    while(n){
        if(n & 1)ret = ret * x % mod;
        x = x * x % mod;
        n >>= 1;
    }
    return ret;
}
int N , M;
ll a[maxn] , b[maxn] , d[maxn] , prefix[maxn];

int main(){
    scanf("%d %d" , &N , &M);
    for(int i = 1; i <= N; ++i)scanf("%lld" , &d[i]);
    sort(d + 1 , d + 1 + N);
    for(int i = 1; i <= N; ++i)prefix[i] = (prefix[i - 1] + d[i]) % mod;
    for(int i = 1; i <= M; ++i){
        ll a , b; scanf("%lld %lld" , &a , &b);
        int l = 1 , r = N , pos = N + 1;
        // find the smallest pos st d[pos] >= b
        while(l <= r){
            int mid = (l + r) >> 1;
            if(d[mid] >= b){
                pos = mid;
                r = mid - 1;
            }
            else l = mid + 1;
        }
        ID printf("%d of monster is less than %lld\n" , pos - 1 , b);
        int cnt_less = pos - 1 , cnt_greater = N - cnt_less;
        if(cnt_greater < a){
            printf("0\n");
        }
        else{
            ll ans = 0;
            ll psmall = (1 - (a * qpow(cnt_greater + 1 , mod - 2) % mod) + mod) % mod;
            ll plarge = (1 - (a * qpow(cnt_greater , mod - 2) % mod) + mod) % mod;
            psmall = psmall * (prefix[pos - 1]) % mod;
            plarge = plarge * (prefix[N] - prefix[pos - 1]) % mod;
            ans = (ans + psmall + plarge) % mod;
            printf("%lld\n" , (ans + mod) % mod);
        }
    }
}