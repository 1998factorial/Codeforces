/*
    Math , Pattern print , prefix sum
    to count how many x in [l , r] such that x % a % b != x % b % a
    It is easier to count the number of x such that x % a % b = x % b % a
    for a given pair of (a , b) , x in [1 , a * b] such that x % a % b = x % b % a
    has same pattern as in [a * b + 1 , a * b * 2]
    and so on.
    let cnt[i] = # of x in [0 , i] such that x % a % b = x % b % a
    for any given query [l , r] , return r - l + 1 - (count(r) - count(l - 1))
    where count(r) returns number of x in [1 , r] that satisfies x % a % b = x % b % a
    Using the cycle pattern, we can first get the number of [1 , a * b] intervals in
    [1 , r] , and for the remaining part, we use modules.
*/

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;


ll cnt[40005];
ll a , b , q;

ll count(ll x){
    ll ret = 0;
    ret += cnt[a * b] * (x / (a * b));
    ret += cnt[x % (a * b)];
    return ret;
}

int main(){
    int t; cin >> t;
    while(t--){
        cnt[0] = 0;
        cin >> a >> b >> q;
        for(ll i = 1; i <= a * b; ++i){
            cnt[i] = cnt[i - 1] + (i % a % b == i % b % a);
        }
        while(q--){
            ll l , r;
            cin >> l >> r;
            cout << r - l + 1 - count(r) + count(l - 1) << endl;
        }
    }
}
