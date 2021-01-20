#include <bits/stdc++.h>
#define MAX_SIZE 524292
typedef long long ll;
using namespace std;

int n;

vector<ll> disc;

ll tmp[MAX_SIZE];

struct segt {
	int lz;
	ll rsum, rlen; 
};

segt tree[MAX_SIZE];

struct line {
	ll x1, x2, y;
};

static bool cmp(const line &a, const line &b) {
	return a.y < b.y;
}

vector<line> rec;

/*
	each node of the tree represents the status of the interval, not end points!!
*/

void build(int l, int r, int index) {
	if (l > r) return;
	if (l == r) {
		tree[index].rlen = disc[r+1] - disc[r];
		return;
	}
	
	int mid = (l + r) >> 1;
	build(l, mid, index << 1);
	build(mid + 1, r, index << 1 | 1);
	tree[index].rlen = tree[index << 1].rlen + tree[index << 1 | 1].rlen;
}

void pushdown(int l, int r, int index) {
	if (l > r) return;
	if (tree[index].lz) {
		if (l != r) {
			tree[index * 2].rsum = tree[index * 2].rlen - tree[index * 2].rsum;
			tree[index * 2 + 1].rsum = tree[index * 2 + 1].rlen - tree[index * 2 + 1].rsum;
			tree[index * 2].lz ^= 1;
			tree[index * 2 + 1].lz ^= 1;
		}
		tree[index].lz = 0;
	}
}

void update(int start, int end, int l, int r, int index) {
	if (start > end || l > end) return;
	pushdown(l, r, index);
	if (start > r || l > end) return;
	if (start <= l && r <= end) {
		tree[index].rsum = tree[index].rlen - tree[index].rsum;
		tree[index].lz = 1;
		return;
	}
	
	int mid = (l + r) >> 1;
	if (end <= mid) {
		update(start, end, l, mid, index * 2);
	} else if (start >= mid + 1) {
		update(start, end, mid + 1, r, index * 2 + 1);
	} else {
		update(start, end, l, mid, index * 2);
		update(start, end, mid + 1, r, index * 2 + 1);
	}
	tree[index].rsum = tree[index * 2].rsum + tree[index * 2 + 1].rsum;
}

ll query() {
	return tree[1].rsum;
}

int main() {
	ll ans = 0;
	int n;
	int j;
	scanf("%d", &n);
	ll x1, y1, x2, y2;
	for (j = 0 ; j < n; j++) {
		// scanf("%I64d%I64d%I64d%I64d", &x1, &y1, &x2, &y2);
		cin >> x1 >> y1 >> x2 >> y2;
		tmp[2 * j] = x1;
		tmp[2 * j + 1] = x2;
		rec.push_back(line{x1, x2, y1});
		rec.push_back(line{x1, x2, y2});
	}
		
	sort(tmp, tmp + 2 * n);
		
	for (j = 0 ; j < 2 * n; j++) {
		if (j == 0 || tmp[j] != tmp[j-1]) {
			disc.push_back(tmp[j]);
		}
	}
		
	sort(rec.begin(), rec.end(), cmp);
	int m = (int) disc.size();
	build(0, m - 2, 1);
	for (j = 0; j < (int) rec.size() - 1; j++) {
		int lx = lower_bound(disc.begin(), disc.end(), rec[j].x1) - disc.begin();
		int rx = lower_bound(disc.begin(), disc.end(), rec[j].x2) - disc.begin();
		update(lx, rx - 1, 0, m - 2, 1);
		ans += query() * (rec[j+1].y - rec[j].y);
	}
	
	// printf("%I64d\n", ans);
	cout << ans << endl;
	return 0;
}
