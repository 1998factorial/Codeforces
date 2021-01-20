#include <bits/stdc++.h>
using namespace std;

int main(){
    int t;cin >> t;
    while(t--){
        string s;
        cin >> s;
        int N = s.size();
        if(N & 1)cout << "NO" << endl;
        else{
            int l = -1 , r = -1;
            for(int i = 0; i < N; ++i){
                if(s[i] == '(') l = i;
                if(s[i] == ')') r = i;
            }
            if(l > r){
                if(r > 0 && l < N - 1)cout << "YES" << endl;
                else cout << "NO" << endl;
            }
            else cout << "YES" << endl;
        }
    }
}