#include <bits/stdc++.h>
#define MAXN 200005
#define EPS 1e-9
#define ID if (1)
using namespace std;
 
int n, c[MAXN];
int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cin >> n;
	for (int i = 1; i <= n; i++) cin >> c[i];
	sort(c+1, c+1+n);
 
	double answer = 1;
	for (int i = 1; i <= n; i++) {
		if (c[i] > i) {
			cout << -1 << endl;
			return 0;
		}
		answer = min(answer, 1.0*c[i]/i);
	}
	cout << answer << endl;
}