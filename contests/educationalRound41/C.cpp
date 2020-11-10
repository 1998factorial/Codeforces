#include <bits/stdc++.h>
#define MAX_SIZE 111
using namespace std;
typedef long long ll;
char a[4][MAX_SIZE][MAX_SIZE];
int cost[4][2];
int main() {
    int n, i, j, k;
    scanf("%d", &n);
    for (i = 0; i < 4; ++i) {
        for (j = 0 ; j < n; ++j) {
            scanf("%s", a[i][j]);
            for (k = 0 ; k < n; ++k) {
                if ((j + k) % 2 != a[i][j][k] - '0') {
                    cost[i][0]++;
                } else {
                    cost[i][1]++;
                }
            }
        }
    }
    int ans = n * n * 4;
    for (i = 0 ; i < 16; ++i) {
        int ret = 0;
        int cnt = 0;
        for (j = 0 ; j < 4; ++j) {
            if (i & (1 << j)) {
                ret += cost[j][0];
                cnt++;
            } else {
                ret += cost[j][1];
            }
        }
        if (cnt == 2) ans = min(ans, ret);
    }
    cout << ans << endl;
    return 0;
}


a[1] = 5
x = 1
count #(a[2 .. 5] >= 1)
x = 2
count #(a[3 .. a[2]] >= 2)

