#include <bits/stdc++.h>
#define MAX_SIZE 100100
using namespace std;
typedef long long ll;

ll p[MAX_SIZE];

int main() {
    int T;
    scanf("%d", &T);
    while (T-- > 0) {
        int i, n;
        ll x;
        int cnt = 0;
        scanf("%d%I64d", &n, &x);
        for (i = 1; i <= n; ++i) {
            scanf("%I64d", &p[i]);
        }
        sort(p + 1, p + 1 + n);
        int lst = n;
        for (i = n; i >= 1; --i) {
            if (p[i] * (lst - i + 1) >= x) {
                lst = i - 1;
                cnt++;
            }
        }
        printf("%d\n", cnt);
    }
    return 0;
}



