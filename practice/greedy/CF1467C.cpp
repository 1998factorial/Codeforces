#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
int sz[3];
vector<int> v[3];
int main(){
    scanf("%d %d %d" ,  &sz[0] , &sz[1] , &sz[2]);
    for(int i = 0; i < 3; ++i){
        for(int j = 0; j < sz[i]; ++j){
            int x;
            scanf("%d" , &x);
            v[i].push_back(x);
        }
        sort(v[i].rbegin() , v[i].rend());
    }
    // if we make a , b st a is gone , b = b - a
    // we link a to b
    // we see that values on even level contribute +
    // values on odd contribute -
    // we further claim that for elements on odd level:
    // either all from one set 
    // or exactly 2 from at 2 different sets
    vector<ll> sum(3);
    vector<int> mn(3);
    for(int i = 0; i < 3; ++i){
        for(int j : v[i]){
            sum[i] += j;
        }
        mn[i] = v[i].back();
    }
    sort(sum.begin() , sum.end());
    sort(mn.begin() , mn.end());
    ll ret = sum[2] + sum[1] - sum[0];
    // odd levels from exactly one set
    ret = max(ret , sum[2] + sum[1] + sum[0] - 2ll * (mn[0] + mn[1]));
    // 2 from 2 different sets
    printf("%lld\n" , ret);

}