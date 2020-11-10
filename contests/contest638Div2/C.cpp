#include <bits/stdc++.h>
using namespace std;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int t; cin >> t;
    while(t--){
        int N , K; cin >> N >> K;
        string s; cin >> s;
        sort(s.begin() , s.end());
        if(s[0] != s[K - 1]){
            cout << s[K - 1] << endl;
            continue;
        }
        cout << s[K - 1];
        if(s[K] != s[N - 1]){
            for(int i = K; i < N; ++i){
                cout << s[i];
            }
            cout << endl;
        }
        else{
            int up = (N - K) / K;
            if((N - K) % K != 0)++up;
            for(int i = 1; i <= up; ++i){
                cout << s[N - 1];
            }
            cout << endl;
        }
    }
}
