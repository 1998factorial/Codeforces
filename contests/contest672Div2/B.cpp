#pragma GCC optimize(3)
#pragma GCC optimize(2)
#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
#define MAX_SIZE 100011
using namespace std;
typedef long long ll;
 
int a[MAX_SIZE];
map<int, int> cnt;
 
int main(){
    int T;
    scanf("%d", &T);
    while (T-- > 0) {
        int n, i, j;
        scanf("%d", &n);
        cnt.clear();
        for (i = 0 ; i < n; ++i) scanf("%d", &a[i]);
        for (i = 0 ; i < 31; ++i) cnt[1 << i] = 0;
        for (i = 0 ; i < n; ++i) {
            for (j = 30; j >= 0; --j) {
                if ((a[i] & (1 << j)) != 0) {
                    cnt[j]++;
                    break;
                }
            }
        }       
        ll ans = 0;
        for (auto iter : cnt) {
            ans += 1ll * iter.second * (iter.second - 1) / 2;
        }
 
        cout << ans << endl;
    }
    return 0;
}