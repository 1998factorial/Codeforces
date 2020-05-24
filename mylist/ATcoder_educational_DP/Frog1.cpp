#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int maxn = 1e5 + 10;
const ll inf = 1e18;
ll h[maxn];
ll DP[maxn];
int N;

ll dis(int i , int j){
    return abs(h[i] - h[j]);
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> N;
    for(int i = 1; i <= N; ++i){
        cin >> h[i];
        DP[i] = inf;
    }
    DP[1] = 0;
    for(int i = 2; i <= N; ++i){
        if(i - 1 >= 1)DP[i] = min(DP[i] , DP[i - 1] + dis(i , i - 1));
        if(i - 2 >= 1)DP[i] = min(DP[i] , DP[i - 2] + dis(i , i - 2));
    }
    cout << DP[N] << endl;
}
