#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const ll inf = 1e18;
int N , W;
ll w[105] , v[105];
ll DP[100005];

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> N >> W;
    for(int i = 1; i <= W; ++i)DP[i] = -inf;
    for(int i = 1; i <= N; ++i){
        cin >> w[i] >> v[i];
    }
    DP[0] = 0;
    for(int i = 1; i <= N; ++i){
        for(int j = W; j >= 0; --j){
            if(j - w[i] >= 0)
                DP[j] = max(DP[j] , DP[j - w[i]] + v[i]);
        }
    }
    ll ret = 0;
    for(int i = 0; i <= W; ++i)ret = max(ret , DP[i]);
    cout << ret << endl;
}
