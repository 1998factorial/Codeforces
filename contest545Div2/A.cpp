#pragma GCC optimize(3)
#pragma GCC optimize(2)
#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
#define MAX_SIZE 200011
using namespace std;
 
int a[MAX_SIZE];
 
int main() {
    int n, i;
    scanf("%d", &n);
    vector<int> disc;
    int curr = 0;
    for (i = 1; i <= n; ++i) scanf("%d", &a[i]);
    for (i = 1; i <= n; ++i) {
        if (i == 1) {
            curr++;
            continue;
        }
        
        if (a[i] == a[i-1]) {
            curr++;
        } else {
            disc.push_back(curr);
            curr = 1;
        }
    }
 
    if (curr > 0) disc.push_back(curr);
    int sz = disc.size();
    int ans = 0;
    for (i = 0 ; i < sz - 1; ++i) {
        ans = max(ans, 2 * min(disc[i], disc[i+1]));
    }
 
    cout << ans << endl;
    return 0;
}