#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

ll t, a, b;
int main() {
	cin >> t;
	while (t--) {
		cin >> a >> b;
		if (a < b) {
			ll c = a;
			a = b;
			b = c;
		}
		if (a >= b * 2) {
			cout << b << endl;
		}
        else {
			ll diff = a - b;
			b -= diff;
			a -= 2 * diff;
			if (a % 3 == 2) {
				cout << (a / 3) * 2 + diff + 1 << endl;
			}
            else {
				cout << (a / 3) * 2 + diff << endl;
			}
		}
	}
}
