#include <bits/stdc++.h>
#define MAX_SIZE 10000011
using namespace std;
 
int p[MAX_SIZE], v[MAX_SIZE], visited[MAX_SIZE];
 
int main() {
    int i, j;
    int a, b, c, d;
    scanf("%d%d%d%d", &a, &b, &c, &d);
    for (i = 2; i < MAX_SIZE; ++i) {
        p[i] = 1;
    }
 
    for (i = 2; i < MAX_SIZE; ++i) {
        if (!visited[i]) {
            for (j = i; j < MAX_SIZE; j += i) {
                visited[j] = 1;
                p[j] *= i;
                v[j]++;
            }
        }
    }
 
    long long ans = 1ll * (d - c + 1) * (b - a + 1);
    for (i = 2; i < MAX_SIZE; ++i) {
        if (p[i] == i) {
            if (v[i] & 1) {
                ans = ans - 1ll * ((d / p[i]) - (c - 1) / p[i]) * ((b / p[i]) - (a - 1) / p[i]);
            } else {
                ans = ans + 1ll * ((d / p[i]) - (c - 1) / p[i]) * ((b / p[i]) - (a - 1) / p[i]);
            }
        }
    }
 
    printf("%lld\n", ans);
    return 0;
}