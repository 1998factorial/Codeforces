#include <bits/stdc++.h>
#define MAX_SIZE 52
using namespace std;
int a[MAX_SIZE][MAX_SIZE];
int b[MAX_SIZE][MAX_SIZE];

vector<pair<int, int>> oper;

int n, m;
 
int main() {
    int i, j;
    scanf("%d%d", &n, &m);
    for (i = 1; i <= n; ++i) {
        for (j = 1; j <= m; ++j) {
            scanf("%d", &a[i][j]);
        }
    }
 
    for (i = 1; i < n; ++i) {
        for (j = 1; j < m; ++j) {
            if (1 <= a[i][j] && 1 <= a[i + 1][j] && 1 <= a[i][j + 1] && 1 <= a[i + 1][j + 1]) {
                oper.emplace_back(i , j);
                b[i][j] = b[i + 1][j] = b[i][j + 1] = b[i + 1][j + 1] = 1;
            }
        }
    }
 
    for (i = 1; i <= n; ++i) {
        for (j = 1; j <= m; ++j) {
            if (a[i][j] != b[i][j]) {
                printf("-1\n");
                return 0;
            }
        }
    }
 
    cout << oper.size() << endl;
    for (auto p : oper) {
        printf("%d %d\n", p.first, p.second);
    }
}