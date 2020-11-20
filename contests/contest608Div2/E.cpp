#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
ll N , K;
ll count(ll x){
    ll ret = 0;
    if(x & 1){
        // x , 2x , 2x + 1 , 4x , 4x + 1 , 4x + 2 , 4x + 3
        ++ret;
        for(ll p = 2, y = x * 2; y <= N; y *= 2 , p *= 2){
            ll up = min(N , p - 1 + y);
            ret += up - y + 1;
        }
    }
    else{
        // x , x + 1 , 2x , 2x + 1 , 2x + 2 , 2x + 3 , ...
        ret += 2;
        for(ll p = 4 , y = x * 2; y <= N; y *= 2 , p *= 2){
            ll up = min(N , p - 1 + y);
            ret += up - y + 1;
        }
    }
    return ret;
}

int main(){
    /*
    int f[1e5];
    f[N] = 1;
    for(int i = N; i >= 1; --i){
        if(i & 1){
            f[i] = 1 + f[i * 2];
        }
        else{
            f[i] = f[i + 1] + f[2 * i] + 1;
        }
        printf("f[%d] = %d\n" , i , f[i]);
    }
    */
    scanf("%lld %lld" , &N , &K);
    ll ret = 1;
    // B search odd
    ll l = 0 , r = (N % 2 == 0) ? N / 2 - 1 : N / 2;
    while(l <= r){
        ll mid = (l + r) >> 1;
        if(count(mid * 2 + 1) >= K){
            l = mid + 1;
            ret = max(ret , mid * 2 + 1);
        }
        else{
            r = mid - 1;
        }
    }
    // B search even
    l = 1 , r = N / 2;
    while(l <= r){
        ll mid = (l + r) >> 1;
        if(count(mid * 2) >= K){
            l = mid + 1;
            ret = max(ret , mid * 2);
        }
        else{
            r = mid - 1;
        }
    }
    printf("%lld\n" , ret);
}