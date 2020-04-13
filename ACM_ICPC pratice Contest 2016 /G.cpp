#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int N;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> N;
    set<ll> s;
    ll ret = 1e18;
    while(N--){
        ll x; cin >> x;
        auto it = s.upper_bound(x);
        if(it != s.end()){
            ret = min(ret , *it - x);
        }
        s.insert(x);
    }
    cout << ret << endl;
}
