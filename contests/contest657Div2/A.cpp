#include <bits/stdc++.h>
using namespace std;


string t = "abacaba";


int main(){
    int q; cin >> q;
    while(q--){
        int sz; cin >> sz;
        string s; cin >> s;
        int cnt = 0;
        for(int i = 0; i + 6 < sz; ++i){
            int ok = 1;
            for(int j = 0; j < 7; ++j)if(t[j] != s[i + j])ok = 0;
            cnt += ok;
        }
        if(cnt > 1){
            cout << "No" << endl;
        } 
        else if(cnt == 1){
            for(int i = 0; i < sz; ++i){
                if(s[i] == '?')s[i] = 'z';
            }
            cout << "Yes" << endl;
            cout << s << endl;
        }
        else{
            //cout << "non" << endl;
            int found = 0;
            for(int i = 0; i + 6 < sz; ++i){
                int ok = 1;
                for(int j = 0; j < 7; ++j){
                    if(t[j] != s[i + j] && s[i + j] != '?'){
                        ok = 0;
                    }
                }
                if(ok){
                    for(int j = 0; j < 7; ++j){
                        s[i + j] = t[j];
                    }
                    for(int j = 0; j < sz; ++j){
                        if(s[j] == '?')s[j] = 'z';
                    }
                    cout << "Yes" << endl;
                    cout << s << endl;
                    found = 1;
                }
            }
            if(found == 0)cout << "No" << endl;
        }
    }
}