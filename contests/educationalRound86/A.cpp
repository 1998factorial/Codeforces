/*
    Greedy , case work
*/
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;


int main(){
    int t; cin >> t;
    while(t--){
        ll a , b;
        ll x , y;
        cin >> x >> y;
        cin >> a >> b;
        ll v1 = abs(x) , v2 = abs(y);
        ll ret = (v1 + v2) * a;
        if(b <= 2ll * a && ((x <= 0 && y <= 0) || (x >= 0 && y >= 0))){
            ret = min(ret , min(v1 , v2) * b + (max(v2 , v1) - min(v2 , v1)) * a);
        }
        cout << ret << endl;
    }
}
