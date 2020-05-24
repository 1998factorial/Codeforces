#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int maxn = 405;
const ll inf = 1e18;
ll a[maxn];
ll DP[maxn][maxn];
ll sum[maxn];
int N;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> N;
    for(int i = 1; i <= N; ++i){
        cin >> a[i];
        sum[i] = sum[i - 1] + a[i];
    }
    for(int len = 2; len <= N; ++len){
        for(int i = 1; i + len - 1 <= N; ++i){
            int j = i + len - 1;
            DP[i][j] = sum[j] - sum[i - 1];
            ll min_val = inf;
            for(int k = i; k < j; ++k){
                min_val = min(min_val , DP[i][k] + DP[k + 1][j]);
            }
            DP[i][j] += min_val;
        }
    }
    cout << DP[1][N] << endl;
}
