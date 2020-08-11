#include <bits/stdc++.h>
#define MAXN 100005
#define INF 1000000009
using namespace std;
int n;
int v[MAXN], l[MAXN], r[MAXN];
bool notroot[MAXN];
set<int> reachables;
// v[at] should be between lo and hi

void dfs(int at, int lo, int hi) {
    if (v[at] >= lo && v[at] <= hi) reachables.insert(v[at]);
    if (l[at] != -1) {
        dfs(l[at], lo, min(v[at], hi));
    }
    if (r[at] != -1) {
        dfs(r[at], max(v[at], lo), hi);
    }
}
void print_debug(int at, int indent) {
    for (int i = 0; i < indent; i++) printf("\t");
    printf("#%d: %d\n", at, v[at]);
    if (l[at] != -1) print_debug(l[at], indent+1);
    if (r[at] != -1) print_debug(r[at], indent+1);
}
int main() {
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> v[i] >> l[i] >> r[i];
        if (l[i] != -1) notroot[l[i]] = true;
        if (r[i] != -1) notroot[r[i]] = true;
    }
    int root = -1;
    for (int i = 1; i <= n; i++) {
        if (!notroot[i]) root = i;
    }
    dfs(root, -INF, INF);
    int answer = 0;
    for (int i = 1; i <= n; i++) {
        if (reachables.count(v[i]) == 0) answer += 1;
    }
    cout << answer << endl;
}