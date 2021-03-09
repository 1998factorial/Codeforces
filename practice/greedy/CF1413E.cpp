#include <bits/stdc++.h>
using namespace std;
typedef long long ll;


void solve(){
    ll a , b , c , d;
    cin >> a >> b >> c >> d;
    if(a > b * c){
        cout << -1 << endl;
        return ; 
    }
    ll k = a / (b * d);
    cout << a * (k + 1) - (k * (k + 1) / 2) * b * d << endl;
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    int t;
    cin >> t;
    while(t--){
        solve();
    }
}