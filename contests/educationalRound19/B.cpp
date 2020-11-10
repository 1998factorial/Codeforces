#include <bits/stdc++.h>
#define MAXN 100005
#define INF 1000000
#define ll long long int
using namespace std;
ll n, a[MAXN];
int main() {
    cin >> n;
    for (int i = 1; i <= n; i++) cin >> a[i];
    ll sum = 0;
    for (int i = 1; i <= n; i++) {
        if (a[i] > 0) sum += a[i];
    }
    if (sum % 2 == 1) {
        cout << sum << endl;
        return 0;
    }
    ll smallest_pos = INF;
    for (int i = 1; i <= n; i++) {
        if (a[i] > 0 && a[i] % 2 == 1 && a[i] < smallest_pos) {
            smallest_pos = a[i];
        }
    }
    ll largest_neg = -INF;
    for (int i = 1; i <= n; i++) {
        if (a[i] < 0 && a[i] % 2 == -1 && a[i] > largest_neg) {
            largest_neg = a[i];
        }
    }
    largest_neg *= -1;
    sum -= min(smallest_pos, largest_neg);
    cout << sum << endl;
}