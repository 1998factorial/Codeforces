#include <bits/stdc++.h>
#define MAXN 100005
#define ID if (false)
using namespace std;
int t, n, x, y, b[MAXN], a[MAXN];
map<int, int> cnt;
vector<pair<int, int>> pairs; // nth and position of initial color
map<int, set<int>> at; // initial color to positions, potential swaps
set<int> error_at;
int main() {
    cin >> t;
    while (t--) {
        cin >> n >> x >> y;
        cnt.clear();
        pairs.clear();
        at.clear();
        error_at.clear();
        for (int i = 1; i <= n; i++) cin >> b[i];
        for (int i = 1; i <= n; i++) {
            a[i] = b[i];
            cnt[b[i]] += 1;
            pairs.push_back(make_pair(cnt[b[i]], i));
            at[b[i]].insert(i);
        }
        sort(pairs.begin(), pairs.end());
        reverse(pairs.begin(), pairs.end());
        int error_is = -1;
        for (int i = 1; i <= n + 1; i++) {
            if (cnt[i] == 0) {
                error_is = i;
                break;
            }
        }
        // sort by number of occurrences per color
        // write #ERR for most commons (n - y times)
        // switch between remain up to (y-x)//2 times
        // switch between #ERR and some for rest
        int errors = n - y;
        for (int i = 0; i < errors; i++) {
            error_at.insert(pairs[i].second);
            a[pairs[i].second] = error_is;
            at[b[pairs[i].second]].erase(pairs[i].second); // unregister the potential swap
        }
        // switch between remain
        int remain = y - x;
        while (remain >= 2) {
            if (at.size() == 0) break;
            auto& p1 = (*at.begin());
            auto& p2 = (*at.rbegin());
            if (p1.first == p2.first) break;
            int pos1 = (*p1.second.begin());
            int pos2 = (*p2.second.begin());
            a[pos1] = b[pos2];
            a[pos2] = b[pos1];
            p1.second.erase(p1.second.begin());
            p2.second.erase(p2.second.begin());
            if (p1.second.size() == 0) at.erase(p1.first);
            if (p2.second.size() == 0) at.erase(p2.first);
            remain -= 2;
        }
        while (remain >= 1) {
            // use errors
            if (error_at.size() == 0) break;
            if (at.size() == 0) break;
            auto& p1 = (*at.begin());
            int pos1 = (*p1.second.begin());
            int pos2 = (*error_at.begin());
            cout << "reach1" << endl;
            p1.second.erase(p1.second.begin());
            cout << "reach2" << endl;
            error_at.erase(error_at.begin());
            a[pos2] = a[pos1];
            a[pos1] = error_is;
            remain -= 1;
            if (p1.second.size() == 0) at.erase(p1.first);
        }
        if (remain != 0) {
            cout << "NO" << endl;
        } else {
            cout << "YES" << endl;
            for (int i = 1; i <= n; i++) {
                cout << a[i] << ' ';
            }
            cout << endl;
        }
    }
}