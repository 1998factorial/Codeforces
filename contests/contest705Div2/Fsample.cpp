#include <bits/stdc++.h>
using namespace std;

int dp[1005];
vector<vector<int>> T;

int ask(int lx1, int ly1, int rx1, int ry1, int lx2, int ly2, int rx2, int ry2) {
    cout << "? " << rx1 - lx1 + 1 << " " << ry1 - ly1 + 1 << " " << lx1 << " " << ly1
    << " " << lx2 << " " << ly2 << endl;
    int ans;
    cin >> ans;
    return ans;
}

int gcd(int a , int b){
    return a == 0 ? b : gcd(b % a , a);
}

int good(int l, int r) {
    if (l == r) return 1;

    int cnt = (r - l + 1) / 2;
    if (ask(T[l][0], T[l][1], T[l + cnt - 1][2], T[l + cnt - 1][3], T[l + cnt][0], T[l + cnt][1], T[l + 2 * cnt - 1][2], T[l + 2 * cnt - 1][3])) {
        return good(l + cnt, r);
    }
    return 0;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int n, m, cntn = 0, cntm = 0;
    cin >> n >> m;

    for (int i = n; i >= 1; --i) {
        if (n % i != 0 || dp[i] != 0) continue;

        for (int j = 2 * i; j <= n; j += i) {
            if (n % j == 0 && j % i == 0) {
                T = {};
                for (int k = 1; k <= j / i; ++k) {
                    T.push_back({(k - 1) * i + 1, 1, k * i, m});
                }
                if (good(0, (int)T.size() - 1)) dp[i] = 1;
                else dp[i] = 2;
                break;
            }
        }

        if (dp[i] == 2) {
            for (int j = 1; j <= n; ++j) {
                if (i % j == 0) dp[j] = 2;
            }
        }
        else {
            dp[i] = 1;
            for (int j = i; j <= n; ++j) {
                if (dp[j] == 1) {
                    int w = gcd(i, j);
                    for (int pos = w; pos <= n; pos += w) {
                        dp[pos] = 1;
                    }
                }
            }
        }
    }

    for (int i = 1; i <= n; ++i) {
        if (n % i == 0) cntn += (dp[i] == 1);
        dp[i] = 0;
    }

    for (int i = m; i >= 1; --i) {
        if (m % i != 0 || dp[i] != 0) continue;

        for (int j = 2 * i; j <= m; j += i) {
            if (m % j == 0 && j % i == 0) {
                T = {};
                for (int k = 1; k <= j / i; ++k) {
                    T.push_back({1, (k - 1) * i + 1, n, k * i});
                }
                if (good(0, (int)T.size() - 1)) dp[i] = 1;
                else dp[i] = 2;
                break;
            }
        }
        if (dp[i] == 2) {
            for (int j = 1; j <= i; ++j) {
                if (i % j == 0) {
                    dp[j] = 2;
                }
            }
        }
        else {
            dp[i] = 1;
            for (int j = i; j <= m; ++j) {
                if (dp[j] == 1) {
                    int w = gcd(i, j);
                    for (int pos = w; pos <= m; pos += w) {
                        dp[pos] = 1;
                    }
                }
            }
        }
    }

    for (int i = 1; i <= m; ++i) {
        if (m % i == 0) cntm += (dp[i] == 1);
    }
    cout << "! " << cntn * cntm << endl;
    return 0;
}