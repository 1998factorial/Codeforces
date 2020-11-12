#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int INF = 1e9;
int N , K;
char s[205] , t[2];
ll DP[205][205][205];
//DP[i][j][k] = maximal number of subseq t occ if we consider s[..i] using j operations and we have k t[0]


int main(){
    cin >> N >> K;
    cin >> (s + 1);
    cin >> t;
    for(int i = 0; i <= N; ++i){
        for(int j = 0; j <= K; ++j){
            for(int k = 0; k <= N; ++k){
                DP[i][j][k] = -INF;
            }
        }
    }
    DP[0][0][0] = 0;
    for(int i = 0; i < N; ++i){
        for(int j = 0; j <= K; ++j){
            for(int k = 0; k <= i; ++k){
                if(t[0] != t[1]){
                    if(s[i + 1] == t[0]){
                        DP[i + 1][j][k + 1] = max(DP[i + 1][j][k + 1] , DP[i][j][k]);
                        if(j + 1 <= K)DP[i + 1][j + 1][k] = max(DP[i + 1][j + 1][k] , DP[i][j][k] + k);
                    }
                    else if(s[i + 1] == t[1]){
                        DP[i + 1][j][k] = max(DP[i + 1][j][k] , DP[i][j][k] + k);
                        if(j + 1 <= K)DP[i + 1][j + 1][k + 1] = max(DP[i + 1][j + 1][k + 1] , DP[i][j][k]);
                    }
                    else{
                        DP[i + 1][j][k] = max(DP[i + 1][j][k] , DP[i][j][k]);
                        if(j + 1 <= K){
                            DP[i + 1][j + 1][k] = max(DP[i + 1][j + 1][k] , DP[i][j][k] + k);
                            DP[i + 1][j + 1][k + 1] = max(DP[i + 1][j + 1][k + 1] , DP[i][j][k]);
                        }
                    }
                }
                else{
                    if(s[i + 1] == t[0]){
                        DP[i + 1][j][k + 1] = max(DP[i + 1][j][k + 1] , DP[i][j][k] + k);
                    }
                    else{
                        DP[i + 1][j][k] = max(DP[i + 1][j][k] , DP[i][j][k]);
                        if(j + 1 <= K)DP[i + 1][j + 1][k + 1] = max(DP[i + 1][j + 1][k + 1] , DP[i][j][k] + k);
                    }
                }
            }
        }
    }
    ll ret = 0;
    for(int i = 0; i <= K; ++i){
        for(int j = 0; j <= N; ++j){
            ret = max(ret , DP[N][i][j]);
        }
    }
    cout << ret << endl;
}
