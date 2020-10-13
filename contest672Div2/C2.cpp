#include <bits/stdc++.h>
#define N (524288*4)
#define ll long long int
#define INF ((ll) 1e15)
#define x first
#define y second
#define mp make_pair
using namespace std;
 
struct node {
	int s, e;
	ll v[4]; // start plus? end plus?
};
 
node tree[N*2];
 
void init(int at, int s, int e) {
	tree[at].s = s;
	tree[at].e = e;
	tree[at].v[0b00] = 0;
	tree[at].v[0b01] = 0;
	tree[at].v[0b10] = 0;
	tree[at].v[0b11] = 0;
	if (s != e) {
		int m = (s + e) / 2;
		init(at*2+1, s, m);
		init(at*2+2, m+1, e);
	}
}
 
int tree_size = N;
void update(int index, ll value) {
	int at = tree_size - 1 + index;
	tree[at].v[0b00] = value;
	tree[at].v[0b01] = 0;
	tree[at].v[0b10] = 0;
	tree[at].v[0b11] = -value;
	while (at != 0) {
		at = (at - 1) / 2;
		tree[at].v[0b00] = max(
			tree[at*2+1].v[0b00] + tree[at*2+2].v[0b10],
			tree[at*2+1].v[0b01] + tree[at*2+2].v[0b00]
		);
		tree[at].v[0b01] = max(
			tree[at*2+1].v[0b00] + tree[at*2+2].v[0b11],
			tree[at*2+1].v[0b01] + tree[at*2+2].v[0b01]
		);
		tree[at].v[0b10] = max(
			tree[at*2+1].v[0b10] + tree[at*2+2].v[0b10],
			tree[at*2+1].v[0b11] + tree[at*2+2].v[0b00]
		);
		tree[at].v[0b11] = max(
			tree[at*2+1].v[0b11] + tree[at*2+2].v[0b01],
			tree[at*2+1].v[0b10] + tree[at*2+2].v[0b11]
		);
	}
}
 
int next_pot(unsigned int v) {
	v--;
	v |= v >> 1;
	v |= v >> 2;
	v |= v >> 4;
	v |= v >> 8;
	v |= v >> 16;
	v++;
	return v;
}
 
int t, n, q, l, r;
ll a[N];
int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cin >> t;
	while (t--) {
		cin >> n >> q;
		tree_size = next_pot(n);
		init(0, 0, tree_size-1);
		for (int i = 0; i < n; i++) {
			cin >> a[i];
			update(i, a[i]);
		}
		cout << tree[0].v[0b00] << endl;
		while (q--) {
			cin >> l >> r;
			l -= 1;
			r -= 1;
			update(l, a[r]);
			update(r, a[l]);
			swap(a[r], a[l]);
			cout << tree[0].v[0b00] << endl;
		}
	}
}