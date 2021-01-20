#include <bits/stdc++.h>
#define lli long long int
#define MAXN 131072
#define ID if (0)
#define ADD ((lli)1e16)
using namespace std;
 
// maintain rt[n] as the highest value
// increment right half of same value as rt[n]
// increment anything less than rt[n]
// range update index query tree
 
// value, number of such values
int n;
lli me, p[MAXN];
map<lli, int> values;
 
int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cin >> n;
	cin >> me;
	n -= 1;
	for (int i = 1; i <= n; i++) {
		cin >> p[i];
		values[p[i]] += 1;
	}
 
	lli answer = 0;
	int cc = 0; // cumulative count
	for (auto it = values.rbegin(); it != values.rend(); it++) {
		auto next = it;
		++next;
		cc += it->second;
 
		// w = how many consumptions a row can stand up to
		int count = cc;
		int w = 0;
		while (count) {
			w += 1;
			count /= 2;
		}
 
 
		// binary search how many fully eaten rows
		// without achieving the goal
		lli at_h = it->first;
		lli next_h = next == values.rend() ? -ADD : next->first;
		ID printf("cc at %lld is %d\n", at_h, cc);
		lli lo = 0;
		lli hi = (at_h-next_h);
		lli best = 0;
		while (hi >= lo) {
			lli mid = (hi+lo)/2;
			if (at_h-mid <= me-mid*w) {
				// still not enough to reduce "me" down
				// such "me" is lower than at_h
				best = mid;
				lo = mid+1;
			} else {
				hi = mid-1;
			}
		}
 
		// perform the reduction
		at_h -= best;
		me -= best*w;
		answer += best*w;
 
		// perform at most w consumptions
		for (int i = 1; i < w; i++) {
			if (me-i < at_h) {
				cout << (answer+i-1) << endl;
				return 0;
			}
		}
		if (me-w < (at_h-1)) {
			cout << (answer+w-1) << endl;
			return 0;
		}
	}
}