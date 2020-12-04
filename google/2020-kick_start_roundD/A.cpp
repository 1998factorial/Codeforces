#include <bits/stdc++.h>
using namespace std;

int t;
int n;
int v[200005];

int main() {
    cin >> t;
    for (int iter = 1; iter <= t; iter++) {
        cin >> n;
        for (int i = 0; i < n; i++) cin >> v[i];
        int ans = 0;
        int pre = -1;
        for (int i = 0; i < n; i++) {
            if ((i == n - 1 || v[i] > v[i + 1]) && v[i] > pre) ++ans;
            pre = max(pre , v[i]);
        }
        printf("Case #%d: %d\n", iter, ans);
    }
}
