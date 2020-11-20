#include <bits/stdc++.h>
#define ii pair<int, int>
#define x first
#define y second
using namespace std;
#define MAXN 8192
#define ID if (0)
 
int n, m, k, u, v;
int a[MAXN], b[MAXN], c[MAXN];
int reach[MAXN]; // rightmost pos where city i can be defended by sending troops from
int take[MAXN]; // where to take troops at
vector<ii> best;
 
int main() {
	cin >> n >> m >> k;
	for (int i = 1; i <= n; i++) {
		cin >> a[i] >> b[i] >> c[i];
		reach[i] = i;
		best.emplace_back(c[i], i);
	}
	for (int i = 1; i <= m; i++) {
		cin >> u >> v;
		reach[v] = max(reach[v], u);
	}
 
	sort(best.begin(), best.end(), [&](ii a, ii b) {
		if (a.x != b.x) return a.x < b.x;
		else return reach[a.y] < reach[b.y];
	});
	sort(best.begin(), best.end());
	reverse(best.begin(), best.end());
 
	// check if unsolvable
	int remain = k;
	for (int i = 1; i <= n; i++) {
		if (remain < a[i]) { cout << -1 << endl; return 0; }
		remain += b[i];
	}
 
	int answer = 0;
	for (auto [c, i] : best) {
		ID cout << "try take contribution " << c << " at " << i << endl;
		take[reach[i]] += 1;
		bool solvable = true;
		ID cout << "check solvability" << endl;
		int remain = k;
		for (int j = 1; j <= n; j++) {
			ID cout << "remain " << remain << endl;
			if (remain < a[j]) {
				ID cout << "fail solvability" << endl;
				solvable = false; break;
			}
			remain += b[j];
			remain -= take[j];
		}
		if (remain < 0 || !solvable) {
			take[reach[i]] -= 1;
			continue;
		}
		answer += c;
	}
 
	cout << answer << endl;
}