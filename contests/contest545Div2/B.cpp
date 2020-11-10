#include <bits/stdc++.h>
#define ID if (0)
using namespace std;
 
int n;
string a1;
string a2;
int c1[4];
int c2[4];
int t1, t2;
int main() {
	cin >> n >> a1 >> a2;
	for (int i = 0; i < n; i++) {
		int v = ((a1[i]-'0') << 1) + (a2[i]-'0');
		ID cout << bitset<2>(v) << endl;
		if (i < (n/2)) {
			c1[v] += 1;
		} else {
			c2[v] += 1;
		}
	}
	t1 = c1[0b10] + c1[0b11];
	t2 = c2[0b01] + c2[0b11];
	int iters = 10000;
	while (t1 != t2 && (iters--)) {
		// try to swap between c1 and c2
		for (int v1 = 0; v1 < 4; v1++) {
			for (int v2 = 0; v2 < 4; v2++) {
				if (c1[v1] && c2[v2]) {
					// there is potential of swapping
					// contribution of v1 to t1
					// contribution of v2 to t2
					int cn11 = (v1 & 2) ? 1 : 0;
					int cn12 = (v1 & 1) ? 1 : 0;
					int cn21 = (v2 & 2) ? 1 : 0;
					int cn22 = (v2 & 1) ? 1 : 0;
 
					if (abs((t1-cn11+cn21) - (t2-cn22+cn12)) < abs(t1-t2)) {
						c1[v1] -= 1;
						c1[v2] += 1;
						c2[v2] -= 1;
						c2[v1] += 1;
						t1 = t1-cn11+cn21;
						t2 = t2-cn22+cn12;
					}
				}
			}
		}
	}
 
	if (t1 != t2) {
		cout << -1 << endl;
	} else {
		for (int i = 0; i < n; i++) {
			int v = ((a1[i]-'0') << 1) + (a2[i]-'0');
			if (c1[v]) {
				cout << (i+1) << ' ';
				c1[v] -= 1;
			}
		}
		cout << endl;
	}
}