#pragma GCC optimize(3)
#pragma GCC optimize(2)
#include <bits/stdc++.h>
#define DEBUG(x) std::cerr << #x << '=' << x << std::endl
using namespace std;
typedef long long ll;
typedef pair<ll , ll> ii;

const ll mod = 1e9;

void solve(string& s) {
    stack<ll> sta;
    stack<vector<ll> > sta2;
    int times;
    unordered_map<char, int> m;
    m['E'] = 0, m['S'] = 1, m['W'] = 2, m['N'] = 3;
    vector<ll> moves(4, 0) , total(4, 0);
    for(int i = 0; i < s.size(); ++i){
        if(s[i] >= '2' && s[i] <= '9'){
            sta.push(s[i] - '0');
            sta2.push(moves);
            moves = vector<ll>(4, 0);
        }
        else if(s[i] == ')'){
            times = sta.top(); sta.pop();
            vector<ll> prev = sta2.top(); sta2.pop();
            for(int i = 0; i < 4; ++i){
              ll t = (times * moves[i]) % mod;
              moves[i] = (prev[i] + t) % mod;
            }
        }
        else if(s[i] > 'A' && s[i] < 'Z'){
            moves[m[s[i]]] = (moves[m[s[i]]] + 1) % mod;
        }
    }
    ll dx = 0 , dy = 0;
    dy = (dy + moves[0]) % mod;
    dy = (dy - moves[2] + mod) % mod;
    dx = (dx + moves[1]) % mod;
    dx = (dx - moves[3] + mod) % mod;
    cout << (dy + 1) << " " << (dx + 1) << endl;
}

int main(){
    int T; cin >> T;
    string s;
    for(int t = 1; t <= T; ++t){
        cout << "Case #" << t << ": ";
        cin >> s;
        solve(s);
    }
    return 0;
}
