#include <bits/stdc++.h>
#define MAXN 105
#define x first
#define y second
#define ii pair<int, int>
#define mp make_pair
using namespace std;
int n, m, q;
int t, r, c, x;
int answer[MAXN][MAXN];
ii matrix[MAXN][MAXN];
void shift_row(int r) {
    ii tmp = matrix[r][0];
    for (int c = 0; c + 1 < m; c++) {
        matrix[r][c] = matrix[r][c+1];
    }
    matrix[r][m-1] = tmp;
}
void shift_col(int c) {
    ii tmp = matrix[0][c];
    for (int r = 0; r + 1 < n; r++) {
        matrix[r][c] = matrix[r+1][c];
    }
    matrix[n-1][c] = tmp;
}
int main() {
    cin >> n >> m >> q;
    for (int r = 0; r < n; r++) {
        for (int c = 0; c < m; c++) {
            matrix[r][c] = mp(r, c);
        }
    }
    while (q--) {
        cin >> t;
        if (t == 1) {
            cin >> r;
            r -= 1;
            shift_row(r);
        }
        if (t == 2) {
            cin >> c;
            c -= 1;
            shift_col(c);
        }
        if (t == 3) {
            cin >> r >> c >> x;
            r -= 1;
            c -= 1;
            answer[matrix[r][c].x][matrix[r][c].y] = x;
        }
    }
    for (int r = 0; r < n; r++) {
        for (int c = 0; c < m; c++) {
            cout << answer[r][c] << ' ';
        }
        cout << endl;
    }
}