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
        ll p , a , b , c;
        cin >> p >> a >> b >> c;
        ll ka = p / a , kb = p / b , kc = p / c;
        if(ka * a < p)++ka;
        if(kb * b < p)++kb;
        if(kc * c < p)++kc;
        cout << min(ka * a , min(kb * b , kc * c)) - p << endl;
    }

}
