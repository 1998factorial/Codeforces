#include <bits/stdc++.h>
#define ID if (false)
#define int int64_t
using namespace std;
int t, n, k;
int l1, r1;
int l2, r2;
void swap(int& a, int& b) {
    int t = a;
    a = b;
    b = t;
}
int a, b, c;
signed main() {
    cin >> t;
    while (t--) {
        cin >> n >> k;
        cin >> l1 >> r1;
        cin >> l2 >> r2;
        // a = amount already intersected
        // b = amount to bridge the distance
        // c = amount with 1:1 return
        // make sure l1 <= l2
        if (l1 > l2) {
            swap(l1, l2);
            swap(r1, r2);
        }
        if (r1 >= r2) {
            // segment 1 fully contains segment 2
            a = (r2 - l2);
            b = 0;
            c = (l2 - l1) + (r1 - r2);
        } else if (l2 < r1) {
            // some intersection
            a = (r1 - l2);
            b = 0;
            c = (l2 - l1) + (r2 - r1);
        } else {
            a = 0;
            b = l2 - r1;
            c = r2 - l1;
        }
        k -= n * a;
        if (k <= 0) {
            cout << 0 << endl;
            continue;
        }
        ID printf("a = %ld, b = %ld, c = %ld\n", a, b, c);
        // solve the remaining k with b,c
        // use one segment pair first, costing b
        // and then at most c
        int cost = b + min(k,c);
        k -= min(k, c);
        ID printf("cost = %ld, k = %ld\n", cost, k);
        int remain = n - 1;
        while (remain > 0) {
            int next_cost = b + min(k,c);
            if (next_cost >= 2 * k) break; // might as well use 2 per step
            cost += next_cost;
            k -= min(k, c);
            ID printf("cost = %ld, k = %ld\n", cost, k);
            remain -= 1;
        }
        cout << cost + (k*2) << endl;
    }
}