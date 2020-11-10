#include <bits/stdc++.h>
#define MAX_SIZE 3111
typedef long long ll;
using namespace std;
int a[MAX_SIZE];
int cnt[MAX_SIZE];
int fr[MAX_SIZE];
ll ans = 0;
int main() {
    int T, N, i, j;
    scanf("%d", &T);
    while (T-- > 0) {
        ans = 0;
        ll curr = 0;
        map<int, int> mp;
        scanf("%d", &N);
        for (i = 0 ; i < N; ++i) {
            scanf("%d", &a[i]);
            mp[a[i]]++;
        }       
        auto iter = mp.begin();
        while (iter != mp.end()) {
            if (iter->second >= 4)
                ans += 1ll * iter->second * (iter->second - 1) * (iter->second - 2) * (iter->second - 3) / 24;
            ++iter;
        }
        for (i = 0 ; i < N; ++i) {
            memset(cnt, 0, sizeof(int));
            memset(fr, 0, sizeof(fr));
            for (j = i ; j < N; ++j) {
                if (a[i] != a[j]) {
                    cnt[a[j]]++;
                }
            }
            for (j = i; j < N; ++j) {
                if (a[j] == a[i]) {
                    ans += curr;
                } else {
                    curr -= 1ll * fr[a[j]] * cnt[a[j]];
                    fr[a[j]]++;
                    cnt[a[j]]--;
                    curr += 1ll * fr[a[j]] * cnt[a[j]]; 
                }
            }
        }
        cout << ans << endl;
    }
    return 0;
}