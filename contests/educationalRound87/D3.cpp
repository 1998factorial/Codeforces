#pragma GCC optimize(2)
#pragma GCC optimize(3)
#include <bits/stdc++.h>
#define LEFT (index << 1)
#define RIGHT (index << 1 | 1)
#define MID ((l+r)>>1)
#define MAX_SIZE 2097312
using namespace std;
int tree[MAX_SIZE];
int cnt[MAX_SIZE >> 1];
int n;

void build(int l, int r, int index) {
    if (l > r) return;
    if (l == r) {
        tree[index] = cnt[l];
        // cout << l << " " << cnt[l] << endl;
        return;
    }

    build(l, MID, LEFT);
    build(MID + 1, r, RIGHT);
    tree[index] = tree[LEFT] + tree[RIGHT];
}

void change(int pt, int l, int r, int index) {
    if (l > r) return;
    if (pt == l && l == r) {
        tree[index]++;
        return;
    }

    if (pt <= MID) {
        change(pt, l, MID, LEFT);
    } else {
        change(pt, MID + 1, r, RIGHT);
    }

    tree[index] = tree[LEFT] + tree[RIGHT];
}

void extractk(int l, int r, int index, int k) {
    if (l > r) return;
    if (l == r) {
        tree[index]--;
        return;
    }
    if (tree[LEFT] >= k) {
        extractk(l, MID, LEFT, k);
    } else {
        extractk(MID + 1, r, RIGHT, k - tree[LEFT]);
    }
    tree[index] = tree[LEFT] + tree[RIGHT];
}

int get(int l, int r, int index) {
    if (l > r) return 0;
    if (l == r) {
        return l;
    }
    if (tree[LEFT] > 0) {
        return get(l, MID, LEFT);
    }
    return get(MID + 1, r, RIGHT);
}

int main() {
    int v, i;
    int q;
    scanf("%d", &n);
    scanf("%d", &q);
    for (i = 1; i <= n; ++i) {
        scanf("%d", &v);
        cnt[v]++;
    }

    build(1, n, 1);

    while (q > 0) {
        int v;
        scanf("%d", &v);
        if (v > 0) {
            change(v, 1, n, 1);
        } else {
            extractk(1, n, 1, -v);
        }
        --q;
    }

    if (tree[1] == 0) {
        printf("0\n");
    } else {
        printf("%d\n", get(1, n, 1));
    }
    return 0;
}
