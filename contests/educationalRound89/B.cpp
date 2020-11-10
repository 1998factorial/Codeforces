#include <bits/stdc++.h>
using namespace std;

int intersect(int l, int r, int L, int R) {
    if (R <= r && R >= l) return 1;
    if (L <= r && L >= l) return 1;
    if (r >= L && r <= R) return 1;
    if (l >= L && l <= R) return 1;
    return 0;
}

int main(){
    int T;
    scanf("%d", &T);
    while (T-- > 0) {
        int n, x, m;
        scanf("%d%d%d", &n, &x, &m);
        int L = x, R = x;
        while (m-- > 0) {
            int l, r;
            scanf("%d%d", &l, &r);
            if (intersect(l, r, L, R)) {
                L = min(l, L);
                R = max(r, R);
            }
        }

        printf("%d\n", R - L + 1);
    }
    return 0;
}
