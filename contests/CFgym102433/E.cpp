#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int mod = 11092019;
int main(){
    ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
    string s;
    cin >> s;
    vector<int> cnt(26);
    for(int i = 0; i < s.size(); ++i){
        ++cnt[s[i] - 'a'];
    }
    ll ret = 1;
    for(int i = 0; i < 26; ++i){
        ret *= (cnt[i] + 1);
        ret %= mod;
    }
    cout << ret << endl;
}