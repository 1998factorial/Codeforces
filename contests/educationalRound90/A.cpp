#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main(){
    int t;
    cin >> t;
    while(t--){
        ll a , b , c;
        cin >> a >> b >> c;
        // 1 : each cost a
        // 2 : b cost c
        // x = strictly cheaper in the first shop than in the second shop
        // y = strictly cheaper in the second shop than in the first shop
        // a * n < (b / c) * n
        // a * n > (b / c) * n
        if(a >= c)cout << -1 << " ";
        else cout << 1 << " ";
        if(c < b * a)cout << b;
        else cout << -1;
        cout << endl;
    }
}
