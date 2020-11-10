#include <bits/stdc++.h>
using namespace std;

int main() {
    int q;
	cin >> q;
	while (q--) {
        string s, t, p;
		cin >> s >> t >> p;
		int y = 0;
        for(int x = 0; x < t.size(); ++x){
            if(t[x] == s[y]){
                ++y;
            }
        }
        if(y != s.size()){
            cout << "NO" << endl;
            continue;
        }
		vector<int> cnt(26, 0);
		for (char c : s) cnt[c - 'a'] += 1;
		for (char c : p) cnt[c - 'a'] += 1;
		for (char c : t) cnt[c - 'a'] -= 1;
		bool ok = 1;
        for(int c : cnt){
            if(c < 0){
                ok = 0;
            }
        }
		if(ok){
			cout << "YES" << endl;
		}
        else{
			cout << "NO" << endl;
		}
	}
}
