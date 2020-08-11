#include <bits/stdc++.h>
using namespace std;
typedef long long ll;


int main(){
    int t; scanf("%d" , &t);
    while(t--){
        ll N , K , l1 , r1 , l2 , r2 , a , b , c , i;
        scanf("%lld %lld" , &N , &K);
        scanf("%lld %lld %lld %lld" , &l1 , &r1 , &l2 , &r2);
        // assume l1 <= l2
        if(l1 > l2){
            swap(l1 , l2);
            swap(r1 , r2);
        }
        // a = already intersected part
        // b = bridge between two intervals
        // c = the 1 unit per step part
        if(r2 <= r1){
            // embeded
            a = r2 - l2;
            b = 0;
            c = l2 - l1 + r1 - r2;
        }
        else if(l2 <= r1){
            // partial intersect
            a = r1 - l2;
            b = 0;
            c = l2 - l1 + r2 - r1;
        }
        else{
            // no intersect
            a = 0;
            b = l2 - r1;
            c = r2 - l1;
        }
        K -= N * a;
        if(K <= 0){
            printf("0\n");
            continue;
        }
        // need to fix up the first interval in order to have chance for 1 : 2 
        ll ret = b + min(K , c);
        K -= min(K , c);
        // try to use as many as 1 unit per step ones
        // at the end , we need 2 * K extra steps to fix up
        for(i = 2; i <= N; ++i){
            ll steps = b + min(c , K); // connect 2 intervals first , then we can extend all 1:1 until the end or up to K
            ll val = min(K , c); // increments we get from this pair
            if(steps >= K * 2)break; // we might just extend 1 : 2 instead
            ret += steps;
            K -= val;
        }
        printf("%lld\n" , ret + K * 2);
    }
}