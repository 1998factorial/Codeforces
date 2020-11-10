/*
    Constructive
    length will not excceed 3
    then case work
*/
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

ll u , v;

// a[1] + ... + a[n] = v
// a[1] xor ... xor a[n] = u

int main(){
    cin >> u >> v;
    if(u > v){
        cout << -1 << endl;
        return 0;
    }
    if(u == v && !u){
        cout << 0 << endl;
        return 0;
    }
    if(u == v && u){
        cout << 1 << endl;
        cout << u << endl;
        return 0;
    }
    /*u != v and u <= v
    u xor (v - u) / 2 xor (v - u) / 2 = u
    u + (v - u) / 2 + (v - u) / 2 = v
    (a + b) = (u xor x) + x
    a xor b = (u xor x) xor x
    x = (v - u) / 2
    check if u xor x == (v + u) / 2
    */
    if((v - u) & 1){
        cout << -1 << endl;
        return 0;
    }
    ll x = (v - u) / 2;
    if((u ^ x) == (v + u) / 2){
        cout << 2 << endl;
        cout << (ll)(u ^ x) << " " << x << endl;
    }
    else{
        cout << 3 << endl;
        cout << (ll)u << " " << (ll)x << " " << (ll)x << endl;
    }
}
