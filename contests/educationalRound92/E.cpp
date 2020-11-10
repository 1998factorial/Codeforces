#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
    int t; scanf("%d" , &t);
    while(t--){
        ll m , d , w , ww , M , step; 
        scanf("%lld %lld %lld" , &m , &d , &w);
        // w | (x - y)(d - 1)
        // ww = w / gcd(w , d - 1) and ww | (x - y)
        // 1 <= (x - y) <= M = min(d , w)
        // fix diff we can get number of x , y as M - diff
        M = min(d , m);
        ww = w / __gcd(w , d - 1);
        step = M / ww;
        printf("%lld\n" , M * step - ww * step * (step + 1) / 2);
    }
}