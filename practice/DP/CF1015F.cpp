#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int MOD = 1e9 + 7;
int N , M , DP[205][205][205][2] , len[205][2];
char s[205];

int main(){
    scanf("%d" , &N);
    N *= 2;
    scanf("%s" , (s + 1));
    M = strlen(s + 1);
    for(int i = 0; i < M; ++i){
        string t = "";
        for(int j = 1; j <= i; ++j){
            t += s[j];
        }
        t += '(';
        for(int j = 0; j <= i; ++j){
            // starting point at j
            bool ok = 1;
            // t[j...i] = s[1..]
            for(int k = j; k <= i; ++k){
                ok &= s[k - j + 1] == t[k];
            }
            if(ok)len[i][0] = max(len[i][0] , i - j + 1);
        }
        t.pop_back();
        t += ')';
        for(int j = 0; j <= i; ++j){
            // starting point at j
            bool ok = 1;
            // t[j...i] = s[1..]
            for(int k = j; k <= i; ++k){
                ok &= s[k - j + 1] == t[k];
            }
            if(ok)len[i][1] = max(len[i][1] , i - j + 1);
        }
    }
    len[M][0] = len[M][1] = M;
    DP[0][0][0][0] = 1;
    for(int i = 0; i < N; ++i){
        for(int j = 0; j <= i; ++j){
            for(int k = 0; k < M; ++k){
                if(j){ // right
                    DP[i + 1][j - 1][len[k][1]][len[k][1] >= M] += DP[i][j][k][0];
                    if(DP[i + 1][j - 1][len[k][1]][len[k][1] >= M] >= MOD)DP[i + 1][j - 1][len[k][1]][len[k][1] >= M] -= MOD;
                }
                // left
                DP[i + 1][j + 1][len[k][0]][len[k][0] >= M] += DP[i][j][k][0];
                if(DP[i + 1][j + 1][len[k][0]][len[k][0] >= M] >= MOD)DP[i + 1][j + 1][len[k][0]][len[k][0] >= M] -= MOD;
            }
            if(j){ // right
                DP[i + 1][j - 1][M][1] += DP[i][j][M][1];
                if(DP[i + 1][j - 1][M][1] >= MOD)DP[i + 1][j - 1][M][1] -= MOD;
            }
            // left
            DP[i + 1][j + 1][M][1] += DP[i][j][M][1];
            if(DP[i + 1][j + 1][M][1] >= MOD)DP[i + 1][j + 1][M][1] -= MOD;
        }
    }
    printf("%d\n" , DP[N][0][M][1]);
}