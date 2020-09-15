#pragma GCC optimize(3)
#pragma GCC optimize(2)
#include <bits/stdc++.h>
#define MAX_SIZE 200111
typedef long long ll;
using namespace std;
char s[MAX_SIZE], t[MAX_SIZE];
int n;
 
int main() {
    int i;
    int cnt = 0;
    scanf("%d", &n);
    scanf("%s", s);
    scanf("%s", t);
    for (i = 0 ; i < n; ++i) {
        if (s[i] != t[i]) {
            ++cnt;
        }
    }
 
    if (cnt == 0) {
        printf("%d\n", 26 * (n + 1));
        return 0;
    } else if (cnt == 1) {
        printf("2\n");
        return 0;
    } else {
        int frt = 0, bk = 0;
        for (i = 0 ; i < n; ++i) {
            if (s[i] != t[i]) {
                frt = i;
                break;
            }
        }
 
        for (i = n - 1; i >= 0; --i) {
            if (s[i] != t[i]) {
                bk = i;
                break;
            }
        }
 
        bool ok = true;
        for (i = frt; i < bk; ++i) {
            if (s[i] != t[i+1]) {
                ok = false;
                break;
            }
        }
 
        if (ok) {
            printf("1\n");
            return 0;
        }
 
        ok = true;
        for (i = frt + 1; i <= bk; ++i) {
            if (s[i] != t[i-1]) {
                ok = false;
                break;
            }
        }
 
        if (ok) {
            printf("1\n");
            return 0;
        }
    }
    printf("0\n");
    return 0;
}