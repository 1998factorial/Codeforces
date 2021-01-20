#include <bits/stdc++.h>
typedef long long ll;
using namespace std;
const int maxn = 1e6 + 10;
ll l , r;

int main(){
    ll ret = 0;
    cin >> l >> r;
    for(ll i = 1; i < maxn; ++i){
        ll j = l / i * i;
        if(j < l)j += i;
        for(; j <= r; j += i){
            if(i * i < j){
                ret += i + j / i;
            }
            else if(i * i == j){
                ret += i;
            }
        }
    }
    cout << ret << endl;
}
