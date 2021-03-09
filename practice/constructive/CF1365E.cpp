#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
ll a[505];
int N;

/*ll get(ll x , ll y , ll z){
    ll ret = 0;
    for(int i = 59; i >= 0; --i){
        if(
            (x >> i & 1) || (y >> i & 1) || (z >> i & 1)
        ){
            ret |= (1ll << i);
        }
    }
    return ret;
}*/

int main(){
    // guess size of answer is <= 3
    /*
    int m = 75;
    for(int a = 1; a <= m; ++a){
        for(int b = a + 1; b <= m; ++b){
            for(int c = b + 1; c <= m; ++c){
                for(int d = c + 1; d <= m; ++d){
                    int v = 0;
                    for(int i = 30; i >= 0; --i){
                        int cnt = 0;
                        if((1ll << i) & a)++cnt;
                        if((1ll << i) & b)++cnt;
                        if((1ll << i) & c)++cnt;
                        if((1ll << i) & d)++cnt;
                        if(cnt >= 2)v |= (1ll << i);
                    }
                    int v2 = 0;
                    v2 = max(v2 , get(a , b , c));
                    v2 = max(v2 , get(a , c , d));
                    v2 = max(v2 , get(a , b , d));
                    v2 = max(v2 , get(c , b , d));
                    assert(v2 >= v);
                }
            }
        }
    }
    */
    cin >> N;
    ll ans = 0;
    for(int i = 1; i <= N; ++i){
        cin >> a[i];
        ans = max(ans , a[i]);
    }
    if(N == 1){
        cout << ans << endl;
        exit(0);
    }
    if(N == 2){
        ans = max(ans , a[1] | a[2]);
        cout << ans << endl;
        exit(0);
    }
    for(int i = 1; i <= N; ++i){
        for(int j = i + 1; j <= N; ++j){
            for(int k = j + 1; k <= N; ++k){
                ans = max(ans , a[i] | a[j] | a[k]);
            }
        }
    }
    cout << ans << endl;
}