#include <bits/stdc++.h>
#define x first
#define y second
#define ID if(1)
using namespace std;
typedef long long ll;
typedef pair<int , int> pii;
const ll INF64 = 1e18 + 10;
const int INF32 = 1e9 + 10;
// we can divide one 1 << k into two 1 << (k-1) in one operation
// find the minimal number of operations to make k many elements 
// that is not greater than 1 << x
ll cnt[35];
int N , Q;

ll solve(ll x , ll k){
    int i;
    ll ret = 0 , small = 0;
    // we can make small deals, one for one.
    for(i = 0; i <= x; ++i){
        small += cnt[i] * ((1ll << i) - 1); 
        k -= cnt[i];
    }
    if(k <= 0)return 0;
    for(i = x + 1; i < N; ++i){
        ll extra = 1ll << (i - x);
        ll need = min(k / extra , cnt[i]);
        k -= need * extra;
        ret += need * (extra - 1);
        small += need * extra * ((1ll << x) - 1);
        if(need < cnt[i])break;
    }
    if(k <= 0)return ret;
    if(i >= N){
        return k <= small ? ret + k : -1;
    }
    // we do not fully split 1 << i into 1 << x
    ll ans = INF64;
    for(; i > x; --i){
        if(small >= k){
            ans = min(ans , k + ret);
        }
        ++ret; // split
        ll extra = (1ll << (i - x - 1));
        if(k >= extra){ // fully split 1 << i - x - 1
            k -= extra;
            ret += extra - 1;
            small += extra * ((1ll << x) - 1);
        }
    }
    return min(ans , ret);
}

int main(){
    scanf("%d %d" , &N , &Q);
    for(int i = 0; i < N; ++i)scanf("%lld" , &cnt[i]);
    while(Q--){
        int t;
        scanf("%d" , &t);
        if(t == 1){
            ll pos , val; 
            scanf("%lld %lld" , &pos , &val);
            cnt[pos] = val;
        }
        else{
            ll x , k;
            scanf("%lld %lld" , &x , &k);
            printf("%lld\n" , solve(x , k));
        }
    }
}