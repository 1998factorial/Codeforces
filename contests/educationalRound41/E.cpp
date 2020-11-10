#include <bits/stdc++.h>
#define MAX_SIZE 524292
typedef long long ll;
using namespace std;
struct segt {
       int left, right;
       int rsum;
};
segt tree[MAX_SIZE * 28];
int root[MAX_SIZE >> 1];
int cnt = 0;
int n = 200000;
int build(int l, int r) {
     if (l > r) return 0;
     int curr = ++cnt;
     if (l == r) return curr;
     int mid = l + (r - l) / 2;
     tree[curr].left = build(l, mid);
     tree[curr].right = build(mid + 1, r);
     return curr;
}
int update(int rt, int pos, int l, int r, int val) {
    if (rt == 0 || l > r || pos < l || pos > r) return rt;
    int curr = ++cnt;
    tree[curr] = tree[rt];
    if (pos == l && l == r) {
       tree[curr].rsum += val;
       return curr;
    }
    
    int mid = l + (r - l) / 2;
    if (pos <= mid) {
       tree[curr].left = update(tree[rt].left, pos, l, mid, val);
    } else {
       tree[curr].right = update(tree[rt].right, pos, mid + 1, r, val);
    }
    
    tree[curr].rsum = tree[tree[curr].left].rsum + tree[tree[curr].right].rsum;
    return curr;
}
int getans(int rt, int start, int end, int l, int r) {
    if (start > end || l > r || rt == 0 || start > r || l > end) return 0;
    if (start <= l && r <= end) return tree[rt].rsum;
    int mid = l + (r - l) / 2;
    if (end <= mid) return getans(tree[rt].left, start, end, l, mid);
    if (start >= mid + 1) return getans(tree[rt].right, start, end, mid + 1, r);
    return getans(tree[rt].left, start, end, l, mid) + getans(tree[rt].right, start, end, mid + 1, r);
}
int query(int l, int r, int d, int u) {
    if (l > r) return 0;
    int ret = getans(root[r], d, u, 1, n) - 
          (l >= 1 ? getans(root[l-1], d, u, 1, n) : 0);
    // cout << ret << endl;
    return ret;
}
int a[MAX_SIZE];
int main() {
    int N, i;
    scanf("%d", &N);
    root[0] = build(1, 200000);
    for (i = 1 ; i <= N; ++i) {
        scanf("%d", &a[i]);
        a[i] = min(a[i], 200000);
        root[i] = update(root[i-1], a[i], 1, 200000, 1);
    }
    ll ans = 0;
    for (i = 1; i <= n; ++i) {
        // if (i+1 > a[i]) continue;
        ans = ans + query(i + 1, min(a[i], N), i, 200000);
    }
    cout << ans << endl;
    return 0;
}