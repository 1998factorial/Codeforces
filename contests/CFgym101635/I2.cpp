#include <iostream>
#include <algorithm>
#include <numeric>
#include <string>
#include <vector>
 
using namespace std;
 
const int N = 1000;
const int M = 5000;
 
int n, m;
vector<int> lad[N];
int a[N][M];
int f[N][10][10];
int rowSum[N][M], nextL[N][M], nextR[N][M];
 
inline int getRowSum(int row, int l, int r)
{
    if (l > r) return 0;
    return rowSum[row][min(r, m - 1)] - (l > 0 ? rowSum[row][l - 1] : 0);
}
 
int main()
{
    cin.tie(NULL); ios_base::sync_with_stdio(false);
    // read input
    cin >> n >> m;
    for (int i = 0; i < n * 2; ++i) {
        string row;
        cin >> row;
        if (i % 2 == 0) {
            for (int j = 0; j < m; ++j)
                if (row[j] != '-')
                    a[i / 2][j] = row[j] - '0';
        }
        else {
            for (int j = 0; j < m; ++j)
                if (row[j] == '|')
                    lad[i / 2].push_back(j);
        }
    }
 
    // preprocess
    for (int i = 0; i < n; ++i) {
        nextL[i][0] = (a[i][0] > 0 ? 0 : -1);
        for (int j = 1; j < m; ++j)
            nextL[i][j] = (a[i][j] > 0 ? j : nextL[i][j - 1]);
 
        nextR[i][m - 1] = (a[i][m - 1] > 0 ? m - 1 : m);
        for (int j = m - 2; j >= 0; --j)
            nextR[i][j] = (a[i][j] > 0 ? j : nextR[i][j + 1]);
 
        partial_sum(a[i], a[i] + m, rowSum[i]);
    }
 
    // solve
    int res = 0;
    for (int i = n - 2; i >= 0; --i) {
        for (size_t j = 0; j < lad[i].size(); ++j)
            for (size_t k = j; k < lad[i].size(); ++k) {
                f[i][j][k] = getRowSum(i + 1, nextL[i + 1][lad[i][j]], nextR[i + 1][lad[i][k]]);
                if (i == 0) res = max(res, f[i][j][k]);
                if (j == k && a[i + 1][lad[i][j]] > 0) continue;
                for (size_t p = 0; p < lad[i + 1].size(); ++p)
                    for (size_t q = p; q < lad[i + 1].size(); ++q) {
                        if (lad[i + 1][q] <= lad[i][j] && getRowSum(i + 1, lad[i + 1][q], lad[i][j]) > 0) continue;
                        if (lad[i][k] <= lad[i + 1][p] && getRowSum(i + 1, lad[i][k], lad[i + 1][p]) > 0) continue;
                        if (p == q && a[i + 1][lad[i + 1][p]] > 0) continue;
 
                        int l1 = nextL[i + 1][min(lad[i][j], lad[i + 1][p])];
                        int r1 = nextR[i + 1][max(lad[i][j], lad[i + 1][p])];
                        int l2 = nextL[i + 1][min(lad[i][k], lad[i + 1][q])];
                        int r2 = nextR[i + 1][max(lad[i][k], lad[i + 1][q])];
                        f[i][j][k] = max(f[i][j][k], f[i + 1][p][q] + getRowSum(i + 1, l1, r2) - getRowSum(i + 1, r1 + 1, l2 - 1));
                    }
                if (i == 0) res = max(res, f[i][j][k]);
            }
    }
    cout << res;
    for(int i = 0; i <= n - 2; ++i){
        for(int l = 0; l < lad[i].size(); ++l){
            for(int r = l; r < lad[i].size(); ++r){
                printf("f[%d][%d][%d] = %d\n" , i + 1 , l + 1 , r + 1 , f[i][l][r]);
            }
        }
    }
    return 0;
}