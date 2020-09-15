#include <bits/stdc++.h>
#define MAXN 100005
using namespace std;
int n, k;
int a[MAXN];
int t[MAXN];
int main() {
    cin >> n >> k;
    for (int i = 1; i <= n; i++) cin >> a[i];
    for (int i = 1; i <= n; i++) cin >> t[i];
    int sum = 0;
    for (int i = 1; i <= n; i++) sum += a[i] * t[i];
    int best_addition = 0;
    int addition = 0;
    for (int i = 1; i <= k; i++) addition += (!t[i]) * a[i];
    best_addition = addition;
    for (int i = k+1; i <= n; i++) {
        addition -= (!t[i-k]) * a[i-k];
        addition += (!t[i]) * a[i];
        best_addition = max(best_addition, addition);
    }
    cout << (sum + best_addition) << endl;
}