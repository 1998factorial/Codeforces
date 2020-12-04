#include <bits/stdc++.h>

using namespace std;

const int maxn = 1e5 + 91;
int arr[maxn], T, N;

int seen[300 * maxn];
int base = 1e7 + 5e6;

void solve() {
    memset(seen , 0 , sizeof(seen));
    long long res = 0, curr = 0;
    seen[base]++;
    for (int i = 0; i < N; ++i) {
        curr += arr[i];
        for (long long j = 0; j <= 3200; ++j) {
            res += seen[curr-j*j+base];
        }
        seen[curr+base]++;
    }
    cout << res << endl;
}


int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> T;
    for (int i = 1; i <= T; ++i) {
        cin >> N;
        for (int j = 0; j < N; ++j) cin >> arr[j];
        cout << "Case #" << i << ": ";
        solve();
    }
    return 0;
}
