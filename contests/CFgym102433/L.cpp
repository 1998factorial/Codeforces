#include <bits/stdc++.h>
using namespace std;
#define ID if (1)
#define BFC 7
#define BFL 9999999
#pragma GCC optimize("Ofast,unroll-loops")

string s;
int v[30];
int digits[30];
int prod[30];
vector<int> pl;
vector<int> ph;
int main() {
	cin >> s;
	reverse(s.begin(),s.end());
	int n = (int) s.length();
	for (int i = 0; i < 25; i++) v[i] = (i >= n) ? 0 : (s[i]-'0');
	for (int i = 0; i <= BFL; i++) {
		// scan through lower 8 digits
		int at = i;
		for (int j = 0; j < BFC; j++) {
			prod[j] = 0;
			digits[j] = at % 10;
			at /= 10;
		}
		for (int a = 0; a < BFC; a++) {
			for (int b = 0; b < (BFC-a); b++) {
				prod[a+b] += digits[a]*digits[b];
				prod[a+b] %= 10;
			}
		}
		bool fail = false;
		for (int j = 0; j < BFC; j++) {
			if (prod[j] != v[j]) {
				fail = true;
				break;
			}
		}
		if (!fail) pl.push_back(i);
	}

	// iterate the top 6 digits
	for (int i = 0; i <= 999999; i++) {
		int at = i;
		for (int j = BFC; j < 13; j++) {
			digits[j] = at % 10;
			at /= 10;
		}
		if (digits[12]*digits[12]%10!=v[24]) continue;
		for (int x : pl) {
			int at = x;
			for (int j = 0; j < BFC; j++) {
				digits[j] = at % 10;
				at /= 10;
			}

			// check all the digits
			for (int j = 0; j < 25; j++) prod[j] = 0;
			for (int a = 0; a < 13; a++) {
				for (int b = 0; b < 13; b++) {
					prod[a+b] += digits[a]*digits[b];
					prod[a+b] %= 10;
				}
			}

			bool fail = false;
			for (int j = BFC; j < 25; j++) {
				if (prod[j] != v[j]) {
					fail = true;
					break;
				}
			}

			if (!fail) {
				bool pr = false;
				for (int j = 12; j >= 0; j--) {
					if (digits[j] == 0 && !pr) continue;
					pr = true;
					cout << digits[j];
				}
				cout << endl;
				return 0;
			}
		}
	}
	cout << -1 << endl;
}