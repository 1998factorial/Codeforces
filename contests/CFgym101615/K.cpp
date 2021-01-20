#include <bits/stdc++.h>
using namespace std;
const int INF = 1e9;
char s[45];
int a[45] , N , M , DP[45][2][2];
// DP[i][j][k] = min operation to make a[1...i] = a[N-i...N] such that 
// we have j "0 to 9" flips passed from a[i + 1] to a[i]
// we have k "0 to 9" flips passed from a[N - i + 1] to a[N - i]
// note that j and k are at most 1, as if a[i + 1] undergoes 2 times "0 to 9"
// then this can be replaced by only once.
int main(){
    scanf("%s" , (s + 1));
    N = strlen(s + 1);
    M = N / 2;
    for(int i = 1; i <= N; ++i)a[i] = s[i] - '0';
    for(int i = 0; i <= N; ++i){
        for(int j = 0; j < 2; ++j){
            for(int k = 0; k < 2; ++k){
                DP[i][j][k] = INF;
            }
        }
    }
    DP[0][0][0] = DP[0][1][0] = 0; // a[1] might bring one or zero "0 to 9" flip to a[0]
    for(int i = 0; i < M; ++i){
        for(int j = 0; j < 2; ++j){
            for(int k = 0; k < 2; ++k){
                if(DP[i][j][k] >= INF)continue;
                int l = i + 1 , r = N - i;
                for(int x = 0; x < 10; ++x){ // flip x times at a[l]
                    for(int y = 0; y < 10; ++y){ // flip y times at a[r]
                        for(int nj = 0; nj < 2; ++nj){
                            int ldigit = a[l] + x + nj , lcarry = 0;
                            int rdigit = a[r] + y + k , rcarry = 0;
                            if(ldigit >= 10)ldigit -= 10 , ++lcarry;
                            if(rdigit >= 10)rdigit -= 10 , ++rcarry;
                            if(lcarry != j)continue; // lcarry does not match with the expected carry passed on a[l - 1], j
                            if(ldigit != rdigit)continue; // we are trying to build a palindrome here
                            DP[i + 1][nj][rcarry] = min(DP[i + 1][nj][rcarry] , DP[i][j][k] + x + y);
                        }
                    }
                }
            }
        }
    }
    int ret = INF;
    if(N & 1){
        for(int x = 0; x < 10; ++x){
            for(int j = 0; j < 2; ++j){
                for(int k = 0; k < 2; ++k){
                    int digit = a[M + 1] + x + k;
                    int carry = (digit >= 10 ? 1 : 0);
                    if(carry != j)continue;
                    ret = min(ret , DP[M][j][k] + x);
                }
            }
        }
    }
    else{
        for(int j = 0; j < 2; ++j){
            ret = min(ret , DP[M][j][j]);
        }
    }
    printf("%d\n" , ret);
}