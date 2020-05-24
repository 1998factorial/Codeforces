/*
    constructive
*/
#include <bits/stdc++.h>
using namespace std;

int main(){
    int t; cin >> t;
    while(t--){
        string s;
        cin >> s;
        int cnt[2];
        cnt[0] = cnt[1] = 0;
        for(int i = 0; i < s.size(); ++i){
            cnt[s[i] - '0']++;
        }
        if(cnt[0] > 0 && cnt[1] > 0){
            for(int i = 0; i < s.size(); ++i)cout << "01";
            cout << endl;
        }
        if(cnt[0] > 0 && cnt[1] == 0){
            cout << s << endl;
        }
        if(cnt[0] == 0 && cnt[1] > 0){
            cout << s << endl;
        }
    }
}
