#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

ll win(ll n, ll k) {
	if (k % 3 != 0) {
		// k has the same effect as 1 or 2
		if (n % 3 == 0) return 0;
		else return 1;
	} else if (k == 3) {
		if (n % 4 == 0) return 0;
		else return 1;
	} else {
		ll rep3s = (k / 3) - 1;
		ll cycle = rep3s * 3 + 4;
		if (n == 0) return 0;
		else if (n == k) return 1;
		else if (n < k) {
			if (n % 3 == 0) return 0;
			else return 1;
		}
		else if (n % cycle == 0) return 0;
		else if ((n % cycle) % 3 == 0 && (n % cycle) / 3 <= rep3s) return 0;
		else return 1;
	}
}

ll t, n, k;
int main() {
	cin >> t;
	while (t--) {
		cin >> n >> k;
		if (win(n, k)) cout << "Alice" << endl;
		else cout << "Bob" << endl;
	}
}
