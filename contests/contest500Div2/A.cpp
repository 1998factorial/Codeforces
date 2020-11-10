#include <bits/stdc++.h>
using namespace std;
 
int n, x, y, sx, sy;
int main() {
	cin >> n;
	for (int i = 1; i <= n; i++) {cin >> x; sx += x;}
	for (int i = 1; i <= n; i++) {cin >> y; sy += y;}
	if (sx >= sy) {
		cout << "Yes" << endl;
	} else {
		cout << "No" << endl;
	}
}