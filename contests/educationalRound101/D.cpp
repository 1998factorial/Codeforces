#include <bits/stdc++.h>
#define ii pair<int, int>
using namespace std;
set<int> keepers = {2,4,16,256,65536};
int t, n;
int main() {
    cin >> t;
    while (t--) {
        vector<ii> ops;
        vector<int> kept;
        cin >> n;
        for (int i = 2; i < n; i++) {
            if (keepers.count(i)) {
                kept.push_back(i);
                continue;
            }
            ops.push_back({i,n});
        }
        // solve n problem
        if (kept.size()) {
            ops.push_back({n,kept.back()});
            ops.push_back({n,kept.back()});
            for (int i = ((int)kept.size())-2; i >= 0; i--) {
                ops.push_back({kept[i+1],kept[i]});
                ops.push_back({kept[i+1],kept[i]});
            }
        }
        cout << ops.size() << endl;
        for (auto [x, y] : ops) {
            cout << x << ' ' << y << endl;
        }
    }
}