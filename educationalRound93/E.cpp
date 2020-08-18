#include <bits/stdc++.h>
#define MAX_SIZE 524292
#define MID ((l+r)>>1)
#define LEFT (index<<1)
#define RIGHT (index<<1|1)
using namespace std;
typedef long long ll;
 
int n;
int op[MAX_SIZE][2];
int tmp[MAX_SIZE];
int tree[MAX_SIZE];
ll tree2[MAX_SIZE];
vector<int> disc;
 
void update(int pt, int l, int r, int index, ll val) {
    if (pt < l || pt > r) return;
    if (l == r) {
        tree[index] += val / abs(val);
        tree2[index] += val;
        return;
    }
 
    if (pt <= MID) {
        update(pt, l, MID, LEFT, val);
    } else {
        update(pt, MID + 1, r, RIGHT, val);
    }
 
    tree[index] = tree[LEFT] + tree[RIGHT];
    tree2[index] = tree2[LEFT] + tree2[RIGHT];
}
 
// get the kth larget number index
int getkth(int l, int r, int index, int k) {
    if (l > r || k < 0) return 0; 
    if (l == r) return l;
    if (k <= tree[RIGHT]) {
        return getkth(MID + 1, r, RIGHT, k);
    }
 
    return getkth(l, MID, LEFT, k - tree[RIGHT]);
}
 
ll query(int start, int end, int l, int r, int index) {
    if (start > end || l > r || start > r || l > end) return 0;
    if (start <= l && r <= end) return tree2[index];
    return query(start, end, l, MID, LEFT) + query(start, end, MID + 1, r, RIGHT); 
}
 
int query2(int start, int end, int l, int r, int index) {
    if (start > end || l > r || start > r || l > end) return 0;
    if (start <= l && r <= end) return tree[index];
    return query2(start, end, l, MID, LEFT) + query2(start, end, MID + 1, r, RIGHT); 
}
 
multiset<int> tp1;
int cnt2 = 0;
ll ans = 0;
    
int main() {
    int i;
    scanf("%d", &n);
    for (i = 1; i <= n; ++i) {
        scanf("%d%d", &op[i][0], &op[i][1]);
        tmp[i] = abs(op[i][1]);
    }
 
    sort(tmp + 1, tmp + 1 + n);
 
    for (i = 1; i <= n; ++i) {
        if (i == 1 || tmp[i] != tmp[i-1]) {
            disc.push_back(tmp[i]);
        }
    }
 
    int sz = disc.size();
    for (i = 1; i <= n; ++i) {
        ans += op[i][1];
        int idx = lower_bound(disc.begin(), disc.end(), abs(op[i][1])) - disc.begin();
        if (op[i][0] == 0) {
            if (op[i][1] < 0) {
                tp1.erase(tp1.find(-op[i][1]));
            } else {
                tp1.insert(op[i][1]);
            }
        } else {
            cnt2 += op[i][1] / abs(op[i][1]);
        }
 
        update(idx, 0, sz - 1, 1, op[i][1]);
        idx = getkth(0, sz - 1, 1, cnt2);
        // cout << "find " << cnt2 << endl;
        ll num = query(idx + 1, sz - 1, 0, sz - 1, 1);
        int ct = query2(idx + 1, sz - 1, 0, sz - 1, 1);
        num += 1ll * (cnt2 - ct) * disc[idx];
        int up = tp1.empty() ? 0 : *tp1.rbegin();
        ll ret = ans + num;
        if (cnt2 != 0 && up < disc[idx]) {
            ret += up - disc[idx];
        }
        printf("%lld\n", ret);
    }
    return 0;
}

