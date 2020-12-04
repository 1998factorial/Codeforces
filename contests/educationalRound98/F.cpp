#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll INF = 1e18 + 10;
int N , Q;
ll cnt[35];

// for all 1 << i , i <= x , one for one
// for 1 << (x + k) , 1 << k for (1 << k) - 1
// we should act greedily , choose from i = x + 1 to N - 1

ll solve(int x , ll k){
    ll small = 0 , ret = 0;
    int i;
    for(i = 0; i <= x; ++i){
        small += ((1ll << i) - 1) * cnt[i];
        k -= cnt[i];
    }
    if(k <= 0)return 0;
    for(i = x + 1; i < N; ++i){
        ll extra = 1ll << (i - x);
        ll need = min(k / extra , cnt[i]);
        k -= need * extra;
        ret += need * (extra - 1);
        small += need * extra * ((1ll << x) - 1);
        if(need != cnt[i])break;
    }
    if(k <= 0)return ret;
    if(i >= N){
        return small < k ? -1 : k + ret;
    }
    ll ans = INF;
    for(; i > x; --i){
        if(small >= k){
            ans = min(ans , ret + k);
        }
        // split (1 << i) into 2 of 1 << (i - 1) 
        ++ret;
        ll extra = (1ll << (i - 1 - x));
        if(extra <= k){
            ret += extra - 1;
            k -= extra;
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
            int pos , val;
            scanf("%d %d" , &pos , &val);
            cnt[pos] = val;
        }
        else if(t == 2){
            int x; ll k;
            scanf("%d %lld" , &x , &k);
            // answer the minimal operations required to make at least k elements
            // not greater than 2^x
            printf("%lld\n" , solve(x , k));
        }
    }
}   