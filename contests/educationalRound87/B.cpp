#include <bits/stdc++.h>
using namespace std;

int cnt[4];

bool check(){
    for(int i = 1; i <= 3; ++i){
        if(cnt[i] <= 0)return 0;
    }
    return 1;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int t; cin >> t;
    while(t--){
        string s; cin >> s;
        int i = 0 , j = 0;
        int ans = s.size();
        bool found = 0;
        memset(cnt , 0 , sizeof(cnt));
        for(; i < s.size(); ++i){
            ++cnt[s[i] - '0'];
            //cout << cnt[1] << " " << cnt[2] << " " << cnt[3] << endl;
            while(check()){
                found = 1;
                ans = min(ans , i - j + 1);
                --cnt[s[j] - '0'];
                ++j;
            }
        }
        if(found){
            cout << ans << endl;
        }
        else{
            cout << 0 << endl;
        }
    }
}
