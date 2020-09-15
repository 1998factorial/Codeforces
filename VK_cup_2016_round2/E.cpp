#include <bits/stdc++.h>
#define MAX_SIZE 200111

using namespace std;

int tree[MAX_SIZE];
int n;

int shift(int x) {
	return x & (-x);
}

void update(int pos, int v) {
	if (pos < 1) return;
	while (pos <= n) {
		tree[pos] += v;
		pos += shift(pos);
	}
}

int query(int pos) {
	int ret = 0;
	while (pos > 0) {
		ret += tree[pos];
		pos -= shift(pos);
	}
	return ret;
}

struct qrs {
	// x, y, v, id
	int x, y, v, id, si;
};

qrs vc[MAX_SIZE << 3];
int ans[MAX_SIZE];
qrs tmp[MAX_SIZE << 3];
int cnt = 0;
// we need to support 2 types of queries
// increment(x, y) by 1, increment(x, y) by -1
// and query(1, 1, x, y)
// good news is the timestamp has already be sorted
// in ascending order, we don't need to worry about that
void cdq(int l, int r) {
	if (l >= r) return;
	int mid = (l + r) >> 1;
	cdq(l, mid);
	cdq(mid + 1, r);
	vector<pair<int, int>> hist;
	int i = l, j = mid + 1, k = 0;
	while (i <= mid && j <= r) {
		if (vc[i].x <= vc[j].x) {
			update(vc[i].y, vc[i].v);
			hist.emplace_back(vc[i].y, -vc[i].v);
			tmp[k++] = vc[i++];
		} else {
			ans[vc[j].id] += vc[j].si * query(vc[j].y);
			tmp[k++] = vc[j++];
		}
	}
	
	while (i <= mid) {
		tmp[k++] = vc[i++];
	}
		
	while (j <= r) {
		ans[vc[j].id] += vc[j].si * query(vc[j].y);
		tmp[k++] = vc[j++];
	}
	
	for (i = l; i <= r; ++i) {
		vc[i] = tmp[i-l];
	}
	
	for (auto h : hist) {
		update(h.first, h.second);
	}
}

map<int, int> X, Y;
int op[MAX_SIZE][3];

int main() {
    int i, N;
    scanf("%d", &N);
    for (i = 1; i <= N; ++i) {
        scanf("%d%d%d", &op[i][0], &op[i][1], &op[i][2]);
        X[op[i][1]] = 0;
        Y[op[i][2]] = 0;
    }

    i = 1;
    for (auto &iter : X) {
        iter.second = i++;
    }

    i = 1;
    for (auto &iter : Y) {
        iter.second = i++;
    }

    for (i = 1; i <= N; ++i) {
        op[i][1] = X[op[i][1]];
        op[i][2] = Y[op[i][2]];
    }

    for (i = 1; i <= N; ++i) {
        if (op[i][0] == 1) {
            vc[cnt++] = qrs{op[i][1], op[i][2], 1, i, 0};
        } else if (op[i][0] == 2) {
            vc[cnt++] = qrs{op[i][1], op[i][2], -1, i, 0};
        } else {
            vc[cnt++] = qrs{op[i][1], op[i][2], 0, i, 1};
            vc[cnt++] = qrs{op[i][1], op[i][2] - 1, 0, i, -1};
        }
    }
    
    n = MAX_SIZE - 1;
    cdq(0, cnt - 1);
    
    for (i = 1; i <= N; ++i) {
        if (op[i][0] == 3) {
            printf("%d\n", ans[i]);
        }
    }
    return 0;
}