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
    for(int i = 1; i <= 100000; ++i)DP[i] = inf;
    for(int i = 1; i <= N; ++i){
        cin >> w[i] >> v[i];
    }
    for(int i = 1; i <= N; ++i){
        for(int j = 100000; j >= 0; --j){
            if(j - v[i] >= 0)
                DP[j] = min(DP[j] , DP[j - v[i]] + w[i]);
        }
    }
    int ret = 0;
    for(int i = 0; i <= 100000; ++i){
        if(DP[i] <= W){
            ret = max(ret , i);
        }
    }
    cout << ret << endl;
}
