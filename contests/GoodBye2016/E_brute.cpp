#include <bits/stdc++.h>
using namespace std;
const int inf = 1e8;
const int maxn = 2e5 + 10;
char a[maxn];
int N , Q , dp[maxn][5][5];

int solve(int l , int r){
    for(int i = l; i <= r; ++i){
        for(int j = 0; j < 5; ++j){
            for(int k = 0; k < 5; ++k){
                dp[i][j][k] = inf;
            }
        }
    }
    if(a[l] == '2'){
        dp[l][0][1] = 0;
        dp[l][0][0] = 1;
    }
    else{
        dp[l][0][0] = 0;
    }
    for(int i = l; i < r; ++i){
        for(int j = 0; j < 5; ++j){
            for(int k = 0; k < 5; ++k){
                if(dp[i][j][k] >= inf)continue;
                if(k == 0){
                    if(a[i + 1] == '2'){
                        dp[i + 1][k][1] = min(dp[i + 1][k][1] , dp[i][j][k]);
                        dp[i + 1][k][k] = min(dp[i + 1][k][k] , dp[i][j][k] + 1);
                    }
                    else{
                        dp[i + 1][k][k] = min(dp[i + 1][k][k] , dp[i][j][k]);
                    }
                }
                if(k == 1){
                    if(a[i + 1] == '0'){
                        dp[i + 1][k][2] = min(dp[i + 1][k][2] , dp[i][j][k]);
                        dp[i + 1][k][k] = min(dp[i + 1][k][k] , dp[i][j][k] + 1);
                    }
                    else{
                        dp[i + 1][k][k] = min(dp[i + 1][k][k] , dp[i][j][k]);
                    }
                }
                if(k == 2){
                    if(a[i + 1] == '1'){
                        dp[i + 1][k][3] = min(dp[i + 1][k][3] , dp[i][j][k]);
                        dp[i + 1][k][k] = min(dp[i + 1][k][k] , dp[i][j][k] + 1);
                    }
                    else{
                        dp[i + 1][k][k] = min(dp[i + 1][k][k] , dp[i][j][k]);
                    }
                }
                if(k == 3){
                    if(a[i + 1] == '7'){
                        dp[i + 1][k][4] = min(dp[i + 1][k][4] , dp[i][j][k]);
                        dp[i + 1][k][k] = min(dp[i + 1][k][k] , dp[i][j][k] + 1);
                    }
                    else if(a[i + 1] == '6'){
                        dp[i + 1][k][k] = min(dp[i + 1][k][k] , dp[i][j][k] + 1);
                    }
                    else{
                        dp[i + 1][k][k] = min(dp[i + 1][k][k] , dp[i][j][k]);
                    }
                }
                if(k == 4){
                    if(a[i + 1] == '6'){
                        dp[i + 1][k][k] = min(dp[i + 1][k][k] , dp[i][j][k] + 1);
                    }
                    else{
                        dp[i + 1][k][k] = min(dp[i + 1][k][k] , dp[i][j][k]);
                    }
                }
            }
        }
    }
    int ret = inf;
    for(int i = 0; i < 5; ++i){
        ret = min(ret , dp[r][i][4]);
    }
    return ret >= inf ? -1 : ret;
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    cin >> N >> Q;
    cin >> (a + 1);
    for(int q = 1; q <= Q; ++q){
        int l , r;
        cin >> l >> r;
        cout << solve(l , r) << endl;
    }
}