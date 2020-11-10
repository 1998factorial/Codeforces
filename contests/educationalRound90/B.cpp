#include <bits/stdc++.h>
using namespace std;

int main(){
    int t; cin >> t;
    while(t--){
        string s; cin >> s;
        vector<int> cnt(2);
        for(char i : s)cnt[i - '0']++;
        int c = min(cnt[0] , cnt[1]);
        if(c % 2 == 0){
            cout << "NET" << endl;
        }
        else{
            cout << "DA" << endl;
        }
    }
}
