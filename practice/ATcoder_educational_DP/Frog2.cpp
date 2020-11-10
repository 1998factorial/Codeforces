#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int maxn = 1e5 + 10;
const ll inf = 1e18;
ll h[maxn];
ll DP[maxn];
int N , K;

ll dis(int i , int j){
    return abs(h[i] - h[j]);
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> N >> K;
    for(int i = 1; i <= N; ++i){
        cin >> h[i];
        DP[i] = inf;
    }
    DP[1] = 0;
    for(int i = 2; i <= N; ++i){
        for(int j = i - 1; j >= i - K && j >= 1; --j){
            DP[i] = min(DP[i] , DP[j] + dis(i , j));
        }
    }
    cout << DP[N] << endl;
}
