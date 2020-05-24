#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const ll mod = 1e9 + 7;
int a[105];
ll DP[105][100005];
ll sum[100005];
int K;
int N;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> N >> K;
    for(int i = 1; i <= N; ++i){
        cin >> a[i];
    }
    DP[0][0] = 1;
    for(int i = 1; i <= N; ++i){
        sum[0] = DP[i - 1][0];
        for(int j = 1; j <= K; ++j){
            sum[j] = (sum[j - 1] + DP[i - 1][j]) % mod;
        }
        for(int j = 0; j <= K; ++j){
            //DP[i][j] = DP[i - 1][j] + ... + DP[i - 1][max(0 , j - a[i])]
            if(j - a[i] > 0){
                DP[i][j] = (sum[j] - sum[j - a[i] - 1] + mod) % mod;
            }
            else{
                DP[i][j] = sum[j];
            }
        }
    }
    cout << DP[N][K] << endl;
}
