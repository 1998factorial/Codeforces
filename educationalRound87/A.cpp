#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int , int> ii;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int t;
    cin >> t;
    while(t--){
        ll a , b , c , d;
        cin >> a >> b >> c >> d;
        if(a <= b){
            cout << b << endl;
        }
        else{
            if(c <= d){
                cout << -1 << endl;
            }
            else{
                ll cnt = (a - b) / (c - d);
                if((a - b) % (c - d))++cnt;
                ll ret = b + c * cnt;
                cout << ret << endl;
            }
        }
    }
}
