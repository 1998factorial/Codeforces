#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int N , X , p[12];
ll DP[1 << 12][12][705];

// trick to make q[i] increasing, when deciding ones' q value,
// add this value to all other "not yet anounced" people's q value
// this trick is helpful as the original p value ordering is preserved (not yet anounced guys)
// so each time we select a new guy to be the top singer, we can simply assign 
// additional max(0 , p[previous_top] - p[new_guy] + 1) marks to q[new_guy]

// DP[mask][i][j] = # of rankings if we have selected mask people, 
// the current highest ranked people is i, we have j additional marks
// avaiable

int main(){
    cin >> N >> X;
    int max_v = 0;
    for(int i = 0; i < N; ++i){
        cin >> p[i];
        max_v = max(max_v , p[i]);
    }
    for(int i = 0; i < N; ++i){
        if(p[i] >= max_v)continue;
        int left = X - N * (max_v - p[i] + 1);
        if(left < 0)continue;
        DP[1 << i][i][left] = 1;
    }
    for(int mask = 1; mask < 1 << N; ++mask){
        for(int i = 0; i < N; ++i){
            for(int j = 0; j <= X; ++j){
                if(DP[mask][i][j] == 0)continue;
                int np = N - __builtin_popcount(mask);
                for(int ni = 0; ni < N; ++ni){
                    if(mask >> ni & 1)continue;
                    int diff = max(0 , p[i] - p[ni] + 1);
                    int nj = j - diff * np;
                    int nmask = mask | (1 << ni);
                    if(nj < 0)continue;
                    DP[nmask][ni][nj] += DP[mask][i][j];
                }
            }
        }
    }
    ll ans = 0;
    for(int i = 0; i < N; ++i){
        for(int j = 0; j <= X; ++j){
            ans += DP[(1 << N) - 1][i][j];
        }
    }
    cout << ans << endl;
}