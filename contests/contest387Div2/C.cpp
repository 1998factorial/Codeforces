#include <bits/stdc++.h>
#define MAX_SIZE 1011111
typedef long long ll;
using namespace std;
// add[i] means the add[i] task is added at the ith minute
int add[MAX_SIZE];
vector<int> del[MAX_SIZE];
vector<int> g[100011];
int ans[MAX_SIZE];
int num[MAX_SIZE];
set<int> ok;
 
int main() {
	int n, q, i, j;
	scanf("%d%d", &n, &q);
	for (i = 1; i <= n; ++i) ok.insert(i);
	for (i = 1; i <= q; ++i) {
		int ti, di;
		scanf("%d%d%d", &ti, &num[i], &di);
		add[ti] = i, del[ti + di - 1].push_back(i);
	}
 
	for (i = 1; i <= 1000000; ++i) {
		if (add[i] != 0) {
			if ((int) ok.size() >= num[add[i]]) {
				j = num[add[i]];
				while (j > 0) {
					g[add[i]].push_back(*ok.begin());
					ans[add[i]] += g[add[i]].back();
					ok.erase(*ok.begin());
					--j;
				}
			} else {
				ans[add[i]] = -1;
			}
		}
 
		for (auto v : del[i]) {
			for (auto id : g[v]) {
				ok.insert(id);
			}
		}
	}
 
	for (i = 1; i <= q; ++i) {
		printf("%d\n", ans[i]);
	}
	return 0;
}