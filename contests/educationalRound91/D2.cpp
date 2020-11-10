#include <bits/stdc++.h>
#define int int64_t
#define MAXN 200005
#define ID if (false)
using namespace std;
int n, m, x, k, y;
map<int, int> rev_a;
int a[MAXN];
int b[MAXN];
int c[MAXN]; // index of corresponding a
int answer = 0;
bool invalid = false;
void handle_l() {
    int e = c[1];
    int w = e - 1;
    ID printf("e = %d, w = %d\n", e, w);
    // observe the sequence s to e
    if (w == 0) return;
    // find the max between
    int m = a[1];
    for (int j = 1; j < e; j++) {
        m = max(m, a[j]);
    }
    int min_x = 0;
    if (m > a[e]) {
        // must require at least one use of x
        min_x += 1;
        if (w < k) {
            invalid = true;
            return;
        }
    }
    int min_y = w % k;
    int remain = w - (min_x * k) - min_y;
    int remain_mana = 0;
    if (y * k < x) {
        // y is an evident improvement to x
        remain_mana = remain * y;
    } else {
        // x is still better/same as y
        remain_mana = remain / k * x;
    }
    answer += (min_x*x+min_y*y+remain_mana);
}
void handle_r() {
    int s = c[m];
    int w = n - s;
    ID printf("s = %d, w = %d\n", s, w);
    // observe the sequence s to e
    if (w == 0) return;
    // find the max between
    int m = a[s+1];
    for (int j = s+1; j <= n; j++) {
        m = max(m, a[j]);
    }
    int min_x = 0;
    if (m > a[s]) {
        // must require at least one use of x
        min_x += 1;
        if (w < k) {
            invalid = true;
            return;
        }
    }
    int min_y = w % k;
    int remain = w - (min_x * k) - min_y;
    int remain_mana = 0;
    if (y * k < x) {
        // y is an evident improvement to x
        remain_mana = remain * y;
    } else {
        // x is still better/same as y
        remain_mana = remain / k * x;
    }
    answer += (min_x*x+min_y*y+remain_mana);
}
void handle_m() {
    for (int i = 1; i < m; i++) {
        int s = c[i];
        int e = c[i+1];
        int w = e - s - 1;
        ID printf("s = %d, e = %d, w = %d\n", s, e, w);
        // observe the sequence s to e
        if (w == 0) continue;
        // find the max between
        int m = a[s+1];
        for (int j = s+1; j < e; j++) {
            m = max(m, a[j]);
        }
        int min_x = 0;
        if (m > a[s] && m > a[e]) {
            // must require at least one use of x
            min_x += 1;
            if (w < k) {
                invalid = true;
                return;
            }
        }
        int min_y = w % k;
        int remain = w - (min_x * k) - min_y;
        int remain_mana = 0;
        if (y * k < x) {
            // y is an evident improvement to x
            remain_mana = remain * y;
        } else {
            // x is still better/same as y
            remain_mana = remain / k * x;
        }
        answer += (min_x*x+min_y*y+remain_mana);
    }
}
signed main() {
    cin >> n >> m >> x >> k >> y;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        rev_a[a[i]] = i;
    }
    for (int i = 1; i <= m; i++) {
        cin >> b[i];
        if (rev_a[b[i]] == 0) {
            cout << -1 << endl;
            return 0;
        }
        c[i] = rev_a[b[i]];
        if (i > 1 && !(c[i-1] < c[i])) {
            cout << -1 << endl;
            return 0;
        }
    }
    if (!invalid) handle_l();
    if (!invalid) handle_m();
    if (!invalid) handle_r();
    if (!invalid) cout << answer << endl;
    if (invalid) cout << -1 << endl;
}


