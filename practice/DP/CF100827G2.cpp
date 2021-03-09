#include <bits/stdc++.h>
using namespace std;

int N , a[105] , win[105][105][2];

int solve(int l , int r , int who){
    int& ret = win[l][r][who];
    if(~ret)return ret;
    if(l == r)return ret = 1;
    ret = 0;
    if(who){ // Bob
        ret |= !solve(l , r , 0);
    }
    int seen_one = 0;
    for(int m = l; m <= r; ++m){
        if(a[m] == 1)seen_one = 1;
        if(m == l && a[m] < a[m + 1])continue;
        if(m == r && a[m] < a[m - 1])continue;
        if(m > l && m < r && (a[m] < a[m + 1] || a[m] < a[m - 1]))continue;
        if(seen_one){
            int len = (r - m);
            ret |= !solve(l , m - 1 , (len & 1 ? 1 - who : who));
        }
        else{
            int len = (m - l);
            ret |= !solve(m + 1 , r , (len & 1 ? 1 - who : who));
        }
    }
    return ret;
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    int t;
    cin >> t;
    while(t--){
        cin >> N;
        for(int i = 1; i <= N; ++i){
            cin >> a[i];
        }
        memset(win , -1 , sizeof(win));
        if(solve(1 , N , 0)){
            cout << "Alice" << endl;
        }
        else{
            cout << "Bob" << endl;
        }
    }
}