#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
ll N , K , M , D;

int main(){
    cin >> N >> K >> M >> D;
    ll ret = 0;
    /*for(ll x = 1; x <= N; ++x){
        if(x > M)break;
        ll p = N / x;
        ll me = p / K + (p % K != 0);
        if(me > D)continue;
        ret = max(ret , me * x);
    }*/
    for(int d = 1; d <= D; ++d){
        // d = (N / x / K) + [(N / x) % K != 0] 
        // search for good x
        // find maximal x such that (N / x / K) + [(N / x) % K != 0] is at least d
        ll l = 1 , r = M , x = 0;
        while(l <= r){
            ll mid = (l + r) >> 1;
            if((N / mid / K) + ((N / mid) % K != 0) >= d){
                x = mid;
                l = mid + 1;
            }
            else r = mid - 1;
        }
        // ans is at least x * d
        ret = max(ret , x * d);
    }
    cout << ret << endl;
}   