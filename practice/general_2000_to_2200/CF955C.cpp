#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll INF = 1e18;
/*
    fix p , the numbers are bounded by (10^18/p)
    p = 2 , 10^9 , this can be done by finding all square numbers in [L,R]
    which is sqrt(R) - sqrt(L - 1)
    p = 3 or more , 10^6 or less, this can be precomputed
*/  
vector<ll> candidate;

ll sq(ll x){ // binary search to avoid precision error
    ll l = 1 , r = 1e9 , ans = 0;
    while(l <= r){
        ll mid = (l + r) >> 1;
        if(mid * mid <= x){
            ans = mid;
            l = mid + 1;
        }
        else r = mid - 1;
    }
    return ans;
}

int main(){
    int Q;
    scanf("%d" , &Q);
    // preprocess for all p >= 3
    for(ll i = 2; i <= 1000000; ++i){
        for(ll v = i * i * i; v <= INF; v *= i){
            candidate.push_back(v);
            if(v > INF / i)break;
        }
    }
    sort(candidate.begin() , candidate.end());
    candidate.erase(unique(candidate.begin() , candidate.end()) , candidate.end());
    vector<ll> tmp;
    for(ll& v : candidate){ // be careful with overcount of the square numbers
        ll s = sq(v);
        if(s * s != v){
            tmp.push_back(v);
        }
    }
    candidate = tmp;
    while(Q--){
        ll l , r;
        scanf("%lld %lld" , &l , &r);
        ll val = upper_bound(candidate.begin() , candidate.end() , r) - lower_bound(candidate.begin() , candidate.end() , l);
        val += sq(r) - sq(l - 1);
        printf("%lld\n" , val);
    }
}