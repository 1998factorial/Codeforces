#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const ll mod = 1e9 + 7;
const int maxn = 3e3 + 10;
ll DP[maxn][maxn];
ll sum[maxn];
char s[maxn];
int N;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> N;
    for(int i = 1; i < N; ++i){
        cin >> s[i];
    }
    DP[1][1] = 1;
    for(int i = 2; i <= N; ++i){
        sum[0] = DP[i - 1][0];
        for(int j = 1; j <= i - 1; ++j){
            sum[j] = (sum[j - 1] + DP[i - 1][j]) % mod;
        }
        for(int j = 1; j <= i; ++j){
            if(s[i - 1] == '<'){
                DP[i][j] = sum[j - 1];
            }
            else{
                DP[i][j] = (sum[i - 1] - sum[j - 1] + mod) % mod;
            }
        }
    }
    ll ret = 0;
    for(int i = 1; i <= N; ++i){
        ret = (ret + DP[N][i]) % mod;
    }
    cout << ret << endl;
}
