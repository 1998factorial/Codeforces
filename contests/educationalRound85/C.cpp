/*
    Greedy
    Only key is where do we start?
    find minimal waste out of all starting point then we are done
*/
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const ll inf = 1e18;

int main(){
    int t; scanf("%d" , &t);
    while(t--){
        int N;
        scanf("%d" , &N);
        vector<ll> a , b;
        for(int i = 1; i <= N; ++i){
            ll x , y; scanf("%lld %lld" , &x , &y);
            a.push_back(x);
            b.push_back(y);
        }
        ll min_waste = inf;
        ll tot = 0;
        for(int i = 0; i < N; ++i){
            if(i)tot += max(0ll , a[i] - b[i - 1]);
            else tot += max(0ll , a[0] - b[N - 1]);
            if(i)min_waste = min(min_waste , a[i] - max(0ll , a[i] - b[i - 1]));
            else min_waste = min(min_waste , a[i] - max(0ll , a[0] - b[N - 1]));
        }
        printf("%lld\n" , tot + min_waste);
    }
}
