#include <bits/stdc++.h>
#define ll long long int
#define INF ((ll) 1e15)
using namespace std;
 
int t, n, q, a;
int main() {
	cin >> t;
	while (t--) {
		cin >> n >> q;
		ll best_x = -INF;
		ll best_y = 0;
		while (n--) {
			cin >> a;
			ll new_best_x = max(best_x, best_y + a);
			ll new_best_y = max(best_y, best_x - a);
			best_x = new_best_x;
			best_y = new_best_y;
		}
		cout << best_x << endl;
	}
}