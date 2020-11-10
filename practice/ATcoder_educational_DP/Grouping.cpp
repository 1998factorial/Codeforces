#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

ll a[16][16];
ll DP[1 << 16];
ll cost[1 << 16];
bool vis[1 << 16];
int N;

ll solve(int state){
    if(state == 0){
        return 0;
    }
    ll& ret = DP[state];
    if(vis[state]){
        return ret;
    }
    vis[state] = 1;
    for(int subset = state; subset; subset = (subset - 1) & state){
        ret = max(ret , cost[subset] / 2 + solve(state ^ subset));
    }
    return ret;
}

int main(){
    cin >> N;
    for(int i = 0; i < N; ++i){
        for(int j = 0; j < N; ++j){
            cin >> a[i][j];
        }
    }
    for(int i = 0; i < N; ++i){
        for(int s = 0; s < (1 << N); ++s){
            if((1 << i) & s){
                for(int j = 0; j < N; ++j){
                    if((1 << j) & s){
                        cost[s] += a[i][j];
                    }
                }
            }
        }
    }
    cout << solve((1 << N) - 1) << endl;
}
