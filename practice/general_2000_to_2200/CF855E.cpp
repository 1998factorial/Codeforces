#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
ll DP[11][65][1 << 10][2];
int a[65] , len;

ll getdp(int base , int i , int mask , int zero , int eq){
    if(i == 0)return !mask && !zero;
    if(!eq && ~DP[base][i][mask][zero])return DP[base][i][mask][zero];
    ll ret = 0;
    int up = (eq ? a[i] : base - 1);
    for(int d = 0; d <= up; ++d){
        if(zero && d == 0){
            // ignore leading zero
            ret += getdp(base , i - 1 , mask , 1 , eq && d == up);
        }
        else{
            ret += getdp(base , i - 1 , mask ^ (1 << d) , 0 , eq && d == up);
        }
    }
    if(!eq)DP[base][i][mask][zero] = ret;
    return ret;
}

ll solve(ll num , int base){
    len = 0;
    while(num){    
        a[++len] = num % base;
        num /= base;
    }
    return getdp(base , len , 0 , 1 , 1);
}

int main(){
    int Q;
    scanf("%d" , &Q);
    memset(DP , -1 , sizeof(DP));
    while(Q--){
        int b;
        ll l , r;
        scanf("%d %lld %lld" , &b , &l , &r);
        printf("%lld\n" , solve(r , b) - solve(l - 1 , b));
    }
}