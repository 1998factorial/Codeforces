#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int maxn = 1e6 + 10;
ll a[maxn] , b[maxn];
int N;

ll check(ll mid){
    for(int i = 2; i <= N; ++i){
        ll val = b[i - 1] - mid; // amount left in b[i - 1]
        if(val + b[i] < a[i])return -1; // can not do the job
        if(a[i] > val)mid = a[i] - val;
        else mid = 0; // a[i] can be fullfilled
    }
    return b[N] - mid; // return the amount that b[N] will supply a[1]
}

int main(){
    int t; scanf("%d" , &t);
    while(t--){
        scanf("%d" , &N);
        for(int i = 1; i <= N; ++i){
            scanf("%lld" , &a[i]);
        }
        for(int i = 1; i <= N; ++i){
            scanf("%lld" , &b[i]);
        }
        ll l = 0 , r = b[1];
        int f = 0;
        while(l <= r && !f){
            ll mid = (l + r) >> 1;
            ll ret = check(mid);
            if(ret == -1){
                r = mid - 1;
            }
            else{
                if(ret + mid >= a[1]){
                    printf("YES\n");
                    f = 1;
                }
                else{
                    l = mid + 1;
                }
            }
        }
        if(!f)printf("NO\n");
    }
}
