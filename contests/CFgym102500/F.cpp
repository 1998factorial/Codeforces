#include <bits/stdc++.h>
#define iii tuple<int, int, int>
#define sz(x) ((int)(x).size())
#define b0(x) (x[sz(x)-1])
#define b1(x) (x[sz(x)-2])
using namespace std;
 
struct DSU {
	int connected;
	vector<int> parent, sz;
 
	void init(int n) {
		parent = sz = vector<int> (n + 1, 0);
		for (int i = 1; i <= n; i++) {
			parent[i] = i, sz[i] = 1;
		}
		connected = n;
	}
 
	int root(int u) {
		while (u != parent[u]) {
			parent[u] = parent[parent[u]];
			u = parent[u];
		}
		return u;
	}
 
	int getSize(int u) {
		return sz[root(u)];
	}
 
	void join(int u, int v) {
		int ru = root(u);
		int rv = root(v);
		if(ru == rv) return;
		connected--;
		if(sz[ru] > sz[rv]) swap(ru, rv);
		sz[rv] += sz[ru];
		sz[ru] = 0;
		parent[ru] = parent[rv];
	}
};
 
// construct tree from set intersections
int n, m, d;
map<int, vector<int>> c;
DSU dsu;
int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cin >> n;
	for (int i = 1; i <= n; i++) {
		cin >> m;
		while (m--) {
			cin >> d;
			c[d].push_back(i);
		}
	}
	vector<iii> edges;
	dsu.init(n);
	for (auto& [k, v] : c) {
		while (sz(v) >= 2) {
			if (dsu.root(b0(v)) != dsu.root(b1(v))) {
				dsu.join(b0(v), b1(v));
				edges.push_back({b0(v),b1(v),k});
				v.pop_back();
			} else {
				v.pop_back();
			}
		}
	}
	if (sz(edges) != n-1) {
		cout << "impossible" << endl;
		return 0;
	}
	for (auto [x, y, w] : edges) {
		cout << x << ' ' << y << ' ' << w << endl;
	}
}