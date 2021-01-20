#include <bits/stdc++.h>
#define len(x) ((int)(x).length())
using namespace std;
 
int n, m;
string k;
string s;
int main() {
	cin >> n >> m >> k >> s;
	// char kl = k[((int)k.size())-1];
	// char sl = s[((int)s.size())-1];
	// cout << kl << ' ' << sl << endl;
	// int shift = kl - sl;
	// cout << shift << endl;
	// for (char c : s) {
	// 	c = c + shift;
	// 	if (c < 'a') c += 26;
	// 	if (c > 'z') c -= 26;
	// 	cout << c;
	// }
	// cout << endl;
	// cout << (-13 % 5) << endl;
	// for (int i = len(s)-len(k); i < len(s); i++) {
	// 	char a = k[i-(len(s)-len(k))];
	// 	char b = s[i];
	// 	char c = ('a'+(b-a));
	// 	if (c < 'a') c += 26;
	// 	if (c > 'z') c -= 26;
	// 	cout << a << " => " << b << " by " << c << ' ' << (b-a) << " " << (i%26) << endl;
	// }
 
	char ans[len(s)];
	for (int i = 0; i < len(k); i++) {
		ans[len(s)-len(k)+i] = k[i];
	}
 
	for (int i = len(s)-len(k)-1; i >= 0; i--) {
		char a = ans[i+n];
		char b = s[i+n];
		char c = ('a'+(b-a));
		if (c < 'a') c += 26;
		if (c > 'z') c -= 26;
		// cout << a << " => " << b << " by " << c << ' ' << (b-a) << " " << (i%26) << endl;
		ans[i] = c;
	}
	for (int i = 0; i < len(s); i++) {
		cout << ans[i];
	}
	cout << endl;
}