#include <bits/stdc++.h>
using namespace std;

char s[705];
int N , mcl[705][705] , DP[705][705];

int main(){
    scanf("%d" , &N);
    scanf("%s" , s + 1);
    // for each substring of s
    // find its smallest cycle length , being mcl[i][j]
    // DP[i][j] is the min length to compress s[i..j]
    for(int i = 1; i <= N; ++i){
        for(int j = i; j <= N; ++j){
            int len = j - i + 1;
            // find smallest cycle length
            // only check those lengths that are divisible by len
            int ok = 0;
            for(int k = 1; k < len && !ok; ++k){
                if(len % k)continue;
                int ok2 = 1;
                for(int x = i; x <= i + k - 1 && ok2; ++x){
                    for(int y = x; y <= j && ok2; y += k){
                        if(s[y] != s[x]){
                            ok2 = 0;
                            break;
                        }
                    }
                }
                if(ok2){
                    mcl[i][j] = k;
                    ok = 1;
                }
            }
            if(!ok)mcl[i][j] = len;
        }
    }
    for(int i = 1; i <= N; ++i){
        DP[i][i] = 1;
    }
    for(int len = 2; len <= N; ++len){
        for(int i = 1; i + len - 1 <= N; ++i){
            int j = i + len - 1;
            DP[i][j] = len;
            DP[i][j] = min(DP[i][j] , DP[i][i + mcl[i][j] - 1]);
            for(int m = i; m < j; ++m){
                DP[i][j] = min(DP[i][j] , DP[i][m] + DP[m + 1][j]);
            }
        }
    }
    printf("%d\n" , DP[1][N]);
}