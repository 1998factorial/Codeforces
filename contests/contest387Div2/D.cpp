#include <bits/stdc++.h>
#define MAX_SIZE 201111
typedef long long ll;
using namespace std;
int n, k;
int a[MAX_SIZE];
vector<pair<int, int>> itv;
vector<int> dist;
 
int main() {
	int i;
	scanf("%d%d", &n, &k);
	for (i = 1; i <= n; ++i) {
		scanf("%d", &a[i]);
		if (a[i] < 0) {
			a[i] = 1;
		} else {
			a[i] = 0;
		}
	}
 
	int l = -1, r = -1;
	int curr = 0, cnt = 0;
	for (i = 1 ; i <= n; ++i) {
		if (curr != a[i]) {
			curr = a[i];
			cnt++;
		}
 
		if (a[i] == 1) {
			if (l == -1) {
				l = i, r = i;
			} else {
				r++;
			}
		} else {
			if (r != -1) {
				itv.emplace_back(l, r);
				l = -1, r = -1;
			}
		}
	}
 
	if (l != -1) {
		itv.emplace_back(l, r);
	}
 
	curr = 0;
	// cout << cnt << endl;
	for (auto v : itv) {
		// cout << v.first << " " << v.second << endl;
		curr += v.second - v.first + 1;
	}
 
	if (curr > k) {
		printf("-1\n");
		return 0;
	}
 
	int sz = itv.size();
	for (i = 0 ; i < sz - 1; ++i) {
		dist.push_back(itv[i+1].first - itv[i].second - 1);
	}
 
	sort(dist.begin(), dist.end());
	for (i = 0 ; i < (int) dist.size(); ++i) {
		if (dist[i] + curr <= k) {
			curr += dist[i];
			// cout << "get one" << endl;
			cnt -= 2;
		}
	}
 
	if (!itv.empty() && a[n] == 0 && curr + n - itv.back().second <= k) {
		cnt--;
	}
	printf("%d\n", cnt);
	return 0;
}