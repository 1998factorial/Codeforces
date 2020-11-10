/*
    how many paths go through centroid of T which has length k ?
*/
#include <cstdio>
#include <vector>
#include <algorithm>
#include <functional>
#include <map>
#include <cassert>
#include <cmath>
using namespace std;

int OneCentroid(int root, const vector<vector<int>> &g, const vector<bool> &dead) {
        static vector<int> sz(g.size());
        function<void (int, int)> get_sz = [&](int u, int prev) {
                sz[u] = 1;
                for (auto v : g[u]) if (v != prev && !dead[v]) {
                        get_sz(v, u);
                        sz[u] += sz[v];
                }
        };
        get_sz(root, -1);
        int n = sz[root];
        function<int (int, int)> dfs = [&](int u, int prev) {
                for (auto v : g[u]) if (v != prev && !dead[v]) {
                        if (sz[v] > n / 2) {
                                return dfs(v, u);
                        }
                }
                return u;
        };
        return dfs(root, -1);
}

vector<int> CentroidDecomposition(const vector<vector<int>> &g, const vector<vector<pair<int, int>>> &l, int q) {
        int n = (int) g.size();
        vector<int> ans(q, 0);
        vector<bool> dead(n, false);
        function<void (int)> rec = [&](int start) {
                int c = OneCentroid(start, g, dead);
                dead[c] = true;
                for (auto u : g[c]) if (!dead[u]) {
                        rec(u);
                }

                /* 
                        changed from here
                */
                map<int, int> cnt;
                function<void (int, int, int, bool)> add_cnt = [&](int u, int prev, int d, bool add) {
                        cnt[d] += (add ? 1 : -1);
                        for (auto v : g[u]) if (v != prev && !dead[v]) {
                                add_cnt(v, u, d + 1, add);
                        }
                };
                function<void (int, int, int)> calc = [&](int u, int prev, int d) {
                        for (auto it : l[u]) {
                                int dd, idx;
                                tie(dd, idx) = it;
                                if (dd - d >= 0 && cnt.count(dd - d)) {
                                        ans[idx] += cnt[dd - d];
                                }
                        }
                        for (auto v : g[u]) if (v != prev && !dead[v]) {
                                calc(v, u, d + 1);
                        }
                };
                add_cnt(c, -1, 0, true);
                for (auto it : l[c]) {
                        int dd, idx;
                        tie(dd, idx) = it;
                        ans[idx] += cnt[dd];
                }
                for (auto u : g[c]) if (!dead[u]) {
                        add_cnt(u, c, 1, false);
                        calc(u, c, 1);
                        add_cnt(u, c, 1, true);
                }
                //

                dead[c] = false;
        };
        rec(0); 
        return ans;
}

int main() {
        int n, q;
        scanf("%d %d", &n, &q);
        vector<vector<int>> g(n);
        for (int i = 0; i < n - 1; i ++) {
                int a, b;
                scanf("%d %d", &a, &b);
                a --, b --;
                g[a].push_back(b);
                g[b].push_back(a);
        }
        vector<vector<pair<int, int>>> l(n); //dist, query idx
        for (int i = 0; i < q; i ++) {
                int v, k;
                scanf("%d %d", &v, &k);
                v --;
                l[v].emplace_back(k, i);
        }
        auto ans = CentroidDecomposition(g, l, q);
        for (int i = 0; i < q; i ++) {
                printf("%d\n", ans[i]);
        }
        return 0;
}