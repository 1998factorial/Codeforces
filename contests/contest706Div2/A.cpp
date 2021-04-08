#include <bits/stdc++.h>
using namespace std;

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    int t;
    cin >> t;
    while(t--){
        int N , K;
        cin >> N >> K;
        string s;
        cin >> s;
        if(K == 0){
            cout << "YES" << endl;
            continue;
        }
        int ok = 1 , i = 0;
        for(;i < K; ++i){
            if(s[i] != s[N - 1 - i])ok = 0;
        }
        if(2 * K >= N){
            cout << "NO" << endl;
            continue;
        }
        if(ok){
            cout << "YES" << endl;
        }
        else{
            cout << "NO" << endl;
        }
    }
}