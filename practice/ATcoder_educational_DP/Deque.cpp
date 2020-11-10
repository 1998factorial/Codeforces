#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int maxn = 3e3 + 10;
ll a[maxn];
ll DP[maxn][maxn][2];
ll sum[maxn];
int N;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> N;
    for(int i = 1; i <= N; ++i){
        cin >> a[i];
        DP[i][i][0] = a[i];
        DP[i][i][1] = 0;
        sum[i] = sum[i - 1] + a[i];
    }
    for(int len = 2; len <= N; ++len){
        for(int i = 1; i + len - 1 <= N; ++i){
            int j = i + len - 1;
            ll L0 = DP[i + 1][j][1] + a[i];
            ll R0 = DP[i][j - 1][1] + a[j];
            ll L1 = DP[i + 1][j][0];
            ll R1 = DP[i][j - 1][0];
            if(L0 > R0){
                DP[i][j][0] = L0;
                DP[i][j][1] = L1;
            }
            else if(L0 == R0){
                if(L1 <= R1){
                    DP[i][j][0] = L0;
                    DP[i][j][1] = L1;
                }
                else{
                    DP[i][j][0] = R0;
                    DP[i][j][1] = R1;
                }
            }
            else{
                DP[i][j][0] = R0;
                DP[i][j][1] = R1;
            }
        }
    }
    cout << DP[1][N][0] - DP[1][N][1] << endl;
}
