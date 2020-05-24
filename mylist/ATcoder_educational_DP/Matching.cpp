#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const ll mod = 1e9 + 7;
int a[25][25];
int N;
ll DP[1 << 21][22];
bool vis[1 << 21][22];

ll solve(int state , int pos){
    if(pos == 0){
        return state == 0;
    }
    if(vis[state][pos]){
        return DP[state][pos];
    }
    ll& ret = DP[state][pos];
    vis[state][pos] = 1;
    for(int j = 1; j <= N; ++j){
        if((state & (1 << (j - 1))) && a[pos][j]){
            ret += solve(state ^ (1 << (j - 1)) , pos - 1);
            ret %= mod;
        }
    }
    return DP[state][pos];
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> N;
    for(int i = 1; i <= N; ++i){
        for(int j = 1; j <= N; ++j){
            cin >> a[i][j];
        }
    }
    cout << solve((1 << N) - 1 , N) << endl;
}
