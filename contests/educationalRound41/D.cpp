#include <bits/stdc++.h>
#define MAXN 100005
#define ID if (0)
#define int int64_t
using namespace std;

int n;
int x[MAXN];
int y[MAXN];

bool collinear(int p1, int p2, int p3) {
    ID {
        printf("p1 = %d %d\n", x[p1], y[p1]);
        printf("p2 = %d %d\n", x[p2], y[p2]);
        printf("p3 = %d %d\n", x[p3], y[p3]);
    }
    return ((y[p3] - y[p2]) * (x[p2] - x[p1]) == (y[p2] - y[p1]) * (x[p3] - x[p2])) ;
}

bool used[MAXN];
bool solve(int p1, int p2) {
    // (x[p1], y[p1]) to (x[p2], y[p2]) as the first line
    fill(used+1, used+1+n, false);
    used[p1] = true;
    used[p2] = true;
    ID printf("check use point %d and %d\n", p1, p2);

    for (int i = 1; i <= n; i++) {
        if (used[i]) continue;
        if (collinear(p1, p2, i)) {
            used[i] = true;
        }
    }

    ID for (int i = 1; i <= n; i++) {
        if (used[i]) printf("point %d is in first line\n", i);
    }

    vector<int> unused;
    for (int i = 1; i <= n; i++) {
        if (!used[i]) unused.push_back(i);
    }

    // check if remaining points are in a single line
    if (unused.size() < 2) return true;
    p1 = unused[0];
    p2 = unused[1];
    used[unused[0]] = true;
    used[unused[1]] = true;
    for (int i = 1; i <= n; i++) {
        if (used[i]) continue;
        if (!collinear(p1, p2, i)) return false;
    }
    return true;
}

int32_t main() {
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> x[i];
        cin >> y[i];
    }
    if (n < 3 || solve(1, 2) || solve(2, 3) || solve(1, 3)) {
        cout << "YES" << endl;
    } else {
        cout << "NO" << endl;
    }
}