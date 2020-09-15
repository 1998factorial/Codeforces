#include <bits/stdc++.h>
using namespace std;
set<int> pos[2];
vector<vector<int>> seqs;
string s;
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cin >> s;
    for (int i = 0; i < s.length(); i++) {
        pos[s[i]-'0'].insert(i);
    }
    vector<int> seq;
    while (pos[0].size()) {
        int at = -1;
        int next_type = 0;
        while (true) {
            auto it = pos[next_type].upper_bound(at);
            if (it == pos[next_type].end()) {
                if (next_type == 0) {
                    // cannot find an ending 0
                    cout << -1 << endl;
                    return 0;
                } else {
                    seqs.push_back(seq);
                    seq.clear();
                    break;
                }
            } else {
                seq.push_back(*it);
                at = *it;
                pos[next_type].erase(it);
                next_type = !next_type;
            }
        }
    }
    if (pos[1].size()) {
        cout << -1 << endl;
    } else {
        cout << seqs.size() << endl;
        for (auto seq : seqs) {
            cout << seq.size() << ' ';
            for (int x : seq) {
                cout << (x+1) << ' ';
            }
            cout << endl;
        }
    }
}


