#include <bits/stdc++.h>
typedef long long ll;

using namespace std;


const int maxn = 1e5 + 91;
int a[maxn], T, N;
ll sum[maxn];
set<ll> vis;

void solve() {
    for(int i = 1; i <= N; ++i){
        sum[i] = sum[i - 1] + a[i];
    }
    for(ll i = 0; i * i <= 10000000; ++i){
        vis.insert(i * i);
    }
    ll ret = 0;
    for(int i = 1; i <= N; ++i){
        for(int j = i; j <= N; ++j){
            bool ok = 0;
            if(vis.find(sum[j] - sum[i - 1]) != vis.end()){
                ok = 1;
            }
            ret += ok;
        }
    }
    cout << ret << endl;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> T;
    for (int i = 1; i <= T; ++i) {
        cin >> N;
        for (int j = 1; j <= N; ++j) cin >> a[j];
        cout << "Case #" << i << ": ";
        solve();
    }
    return 0;
}
