#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    int t;
    cin >> t;
    while(t--){
        ll N , ans = 0;
        cin >> N;
        /*for(int a = 1; a <= N; ++a){
            for(int b = 1; b <= N; ++b){
                for(int c = 1; c <= N; ++c){
                    if(a * a + b * b == c * c && c == a * a - b){
                        printf("(%d %d %d)\n" , a , b , c);
                        ++ans;
                    }
                }
            }
        }
        cout << ans << endl;
        */
        // (a , b , c) -> (a , b , b + 1)
        // a * a = 2 * b + 1
        for(ll a = 3; a * a <= N * 2 + 1; ++a){
            ll b2 = (a - 1) * (a + 1);
            if(b2 % 2 != 0)continue;
            ll b = b2 / 2;
            ll c = b + 1;
            if(b <= N && c <= N)++ans;
            //printf("(%lld %lld %lld)\n" , a , b , c);
        }
        cout << ans << endl;
    }
}