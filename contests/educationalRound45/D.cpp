#include <bits/stdc++.h>
#define MAX_SIZE 1011
using namespace std;

int g[MAX_SIZE][MAX_SIZE];
int n;

int main() {
    int a, b, i, j;
    scanf("%d%d%d", &n, &a, &b);
    if (a == 1 && b == 1 && n == 1) {
        printf("YES\n");
        printf("0\n");
        return 0;
    }

    if (a == 1 && b == 1 && (n == 2 || n == 3)) {
        printf("NO\n");
        return 0;
    }

    if (a == 1 && b == 1) {
        for (i = 2; i <= n; ++i) {
            g[i-1][i] = g[i][i-1] = 1;
        }

        printf("YES\n");
        for (i = 1; i <= n; ++i) {
            for (j = 1; j <= n; ++j) {
                printf("%d", g[i][j]);
            }
            printf("\n");
        }
        return 0;
    }

    if (a != 1 && b != 1) {
        printf("NO\n");
        return 0;
    }

    vector<pair<int, int>> edg;
    if (a != 1) {
        for (i = 1, j = n; i < n && j > a; ++i, --j) {
            edg.emplace_back(i, i + 1);
        }

        for (auto e : edg) {
            g[e.first][e.second] = g[e.second][e.first] = 1;
        }

        printf("YES\n");
        for (i = 1; i <= n; ++i) {
            for (j = 1; j <= n; ++j) {
                printf("%d", g[i][j]);
            }
            printf("\n");
        }

        return 0;
    }

    for (i = 1; i <= n; ++i) {
        for (j = 1; j <= n; ++j) {
            if (i != j) {
                g[i][j]  = 1;
            }
        }
    }

    for (i = 1, j = n; i < n && j > b; ++i, --j) {
        edg.emplace_back(i, i + 1);
    }

    for (auto e : edg) {
        g[e.first][e.second] = g[e.second][e.first] = 0;
    }

    printf("YES\n");
    for (i = 1; i <= n; ++i) {
        for (j = 1; j <= n; ++j) {
            printf("%d", g[i][j]);
        }
        printf("\n");
    }
    return 0;
}
