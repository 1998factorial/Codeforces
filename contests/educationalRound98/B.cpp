#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int maxn = 1e5 + 10;
int a[maxn] , N;

int main(){
    int t;
    scanf("%d" , &t);
    while(t--){
        scanf("%d" , &N);
        ll sum = 0;
        multiset<int> vis; 
        for(int i = 1; i <= N; ++i)scanf("%d" , &a[i]) , sum += a[i] , vis.insert(a[i]);
        ll ans = 0;
        for(int i = 1; i <= N; ++i){
            sum -= a[i];
            vis.erase(vis.find(a[i]));
            ll mx = *vis.rbegin();
            ll v = mx * (N - 1) - sum;
            ll p = (ll)a[i] - v;
            if(p <= 0)ans = max(ans , -p);
            else {
                if(p % (N - 1) != 0)
                    ans = max(ans , (ll)(N - 1) - (p % (N - 1)));
            }
            sum += a[i];
            vis.insert(a[i]);
        }
        printf("%lld\n" , ans);
    }
}

