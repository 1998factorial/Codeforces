#include <bits/stdc++.h>
using namespace std;
#define MAXN 500005
#define ii pair<int, int>
#define x first
#define y second
#define lli long long int
#define ID if (1)

lli n, c, r;
lli s[MAXN];
set<int> remain;
lli sign(lli x) {
	if (x > 0) return 1;
	if (x < 0) return -1;
	return 0;
}
int dp[2];
int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cin >> n >> c >> r;
	for (int i = 1; i <= n; i++) cin >> s[i];
	vector<int> order;
	for (int i = 1; i <= n; i++) {
		if (s[i]) {
			order.push_back(i);
			remain.insert(i);
		}
	}
	sort(order.begin(), order.end(), [&](int a, int b) {
		return abs(s[a]) < abs(s[b]);
	});

	// calculate initial alternating sequence length
	// does not consider 0s as "free"
	if (s[1] < 0) dp[0] += 1;
	if (s[1] > 0) dp[1] += 1;
	for (int i = 2; i <= n; i++) {
		int ndp0 = dp[0];
		int ndp1 = dp[1];
		if (s[i] < 0) ndp0 = max(ndp0, dp[1]+1);
		if (s[i] > 0) ndp1 = max(ndp1, dp[0]+1);
		dp[0] = ndp0;
		dp[1] = ndp1;
	}

	int asl = max(dp[0], dp[1]);
	lli answer = (n-asl)*r;

	{
		// recalculate DP which considers all 0s as free
		dp[0] = 0;
		dp[1] = 0;
		if (s[1] <= 0) dp[0] += 1;
		if (s[1] >= 0) dp[1] += 1;
		for (int i = 2; i <= n; i++) {
			int ndp0 = dp[0];
			int ndp1 = dp[1];
			if (s[i] <= 0) ndp0 = max(ndp0, dp[1]+1);
			if (s[i] >= 0) ndp1 = max(ndp1, dp[0]+1);
			dp[0] = ndp0;
			dp[1] = ndp1;
		}
		asl = max(dp[0], dp[1]);
		answer = min(answer, (n-asl)*r+c);
	}

	for (int i : order) {
		// make s[i] free
		auto it = remain.lower_bound(i);
		auto next = it;
		++next;
		if (it != remain.begin() && next != remain.end()) {
			// has something unfreed before and after
			auto prev = it;
			--prev;
			int ai = *prev;
			int bi = *it;
			int ci = *next;
			lli a = s[ai];
			lli b = s[bi];
			lli c = s[ci];
			if (
				(((bi-ai)%2)==(sign(a)==sign(b))) &&
				(((ci-bi)%2)==(sign(b)==sign(c)))
			) {
				asl += 2;
			}
		} else if (it != remain.begin()) {
			// has something unfreed before
			auto prev = it;
			--prev;
			int ai = *prev;
			int bi = *it;
			lli a = s[ai];
			lli b = s[bi];
			if (((bi-ai)%2)==(sign(a)==sign(b))) {
				asl += 1;
			}
		} else if (next != remain.end()) {
			// has something unfreed after
			int bi = *it;
			int ci = *next;
			lli b = s[bi];
			lli c = s[ci];
			if (((ci-bi)%2)==(sign(b)==sign(c))) {
				asl += 1;
			}
		} else {
			// everything else has been freed
			// can't possibly increase asl
		}
		remain.erase(it);
		answer = min(answer, ((n-asl)*r)+(abs(s[i])+1)*c);
	}
	cout << answer << endl;
}