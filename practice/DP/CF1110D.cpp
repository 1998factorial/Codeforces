/*
    Dynamic programming , rating 2200
    notice that if for some x , we have 3 [x , x + 1 , x + 2] , then it is the same as
    [x , x , x] , [x + 1 , x + 1 , x + 1] , [x + 2 , x + 2 , x + 2]
    so any [x , x + 1 , x + 2] will not appear more than 2 times
    then we can DP on this property
    #[x - 2 , x - 1 , x] <= 2 , #[x - 1 , x , x + 1] <= 2 , #[x , x + 1 , x + 2] <= 2
    DP[x][i][j] = the answer if we only consider the first x numbers , given that #[x - 2 , x - 1 , x] = i
    and #[x - 1 , x , x + 1] = j. then we can enumerate the number of #[x , x + 1 , x + 2] = k
    transit to DP[x + 1][j][k] = DP[x][i][j] + (cnt[x] - i - j - k) / 3 + k.
    ans = DP[M + 1][0][0] as M + 1 does not appear in any of sequence
*/
#include <bits/stdc++.h>
using namespace std;

const int maxn = 1e6 + 10;
int N , M;
int cnt[maxn];
int DP[maxn][3][3];

int main(){
    scanf("%d %d" , &N , &M);
    for(int i = 1; i <= N; ++i){
        int x; scanf("%d" , &x);
        ++cnt[x];
    }
    for(int i = 0; i <= M; ++i){
        for(int j = 0; j <= 2; ++j){
            for(int k = 0; k <= 2; ++k){
                DP[i][j][k] = -1;
            }
        }
    }
    DP[0][0][0] = 0;
    for(int x = 0; x <= M; ++x){
        for(int i = 0; i <= 2; ++i){
            for(int j = 0; j <= 2; ++j){
                if(~DP[x][i][j]){
                    for(int k = 0; k <= 2 && cnt[x] - i - j - k >= 0; ++k){
                        DP[x + 1][j][k] = max(DP[x + 1][j][k] ,  DP[x][i][j] + (cnt[x] - i - j - k) / 3 + k);
                    }
                }
            }
        }
    }
    printf("%d\n" , DP[M + 1][0][0]);
}
