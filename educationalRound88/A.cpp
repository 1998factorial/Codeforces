#include <bits/stdc++.h>
using namespace std;

int main(){
    int t; cin >> t;
    while(t--){
        int n , m , k;
        cin >> n >> m >> k;
        int cnt = n / k;
        if(cnt >= m){
            cout << m << endl;
        }
        else{
            int mm = (m - cnt) / (k - 1) + ((m - cnt) % (k - 1) != 0);
            //cout << "mm = " << mm << endl;
            cout << cnt - mm << endl;
        }
    }
}
