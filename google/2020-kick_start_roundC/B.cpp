#include <bits/stdc++.h>
using namespace std;


int T, R, C;

string dfs(unordered_map<char, vector<char>> g, char curr, unordered_set<char> seen, unordered_map<char, string>& res) {
    seen.insert(curr);
    if (res.find(curr) != res.end()) return res[curr];
    res[curr] = "";
    for (int i = 0; i < g[curr].size(); ++i) {
        if (seen.find(g[curr][i]) != seen.end()) {
            string tmp = dfs(g, g[curr][i], seen, res);
            if (tmp != "") {
                res[curr] = tmp;
                break;
            }
        }
    }
    return res[curr];
}


void solve(vector<string>& wall) {
    unordered_map<char, vector<char>> g;
    unordered_set<char> contain;
    for (int i = R - 1; i >= 0; ++i) {
        for (int j = 0; j < C; ++j) {
            if (i != R-1) {
                g[wall[i][j]].push_back(wall[i-1][j]);
            }
            contain.insert(wall[i][j]);
        }
    }

    string res;
    for (auto c : contain) {
        unordered_map<char, string> m;
        unordered_set<char> seen;
        res = dfs(g, c, seen, m);
        cout << res << endl;
    }
}



int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> T;
    for (int i = 1; i <= T; ++i) {
        cin >> R >> C;
        vector<string> wall = vector<string>(R);
        string tmp;
        for (int j = 0; j < R; ++i) {
            cin >> tmp;
            wall.push_back(tmp);
        }
        cout << "Case #" << i << ": ";
        solve(wall);
    }
    return 0;
}
