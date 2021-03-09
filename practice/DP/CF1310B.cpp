// Lession: For elimination game, try to look at the subtree of the game binary tree
// we will see that after processing a subtree, we have extactly 2 player left, 
// one for upper, one for lower.

// if we only consider the answer in [0 , 2^t - 1]
// it can be computed by [0 , 2^(t-1) - 1] , merged with
// [2^(t-1) , 2^t - 1] as these 2 sets are independent before they meet
// the independence of the subproblem should hint us a DP & divide & conqurer approach
#include <bits/stdc++.h>
using namespace std;
const int INF = 1e9 + 10;
int N , K , isfan[(1 << 17) + 10] , DP[(1 << 17) + 10][18][2][2];
// DP[i][j][x][y] = maximal interesting games for players in [i..i+2^(j)-1], st,
// x=>last team on upper is fan team, y=>last team on lower is fan team
int main(){
    scanf("%d %d" , &N , &K);
    for(int i = 1; i <= K; ++i){
        int x;
        scanf("%d" , &x);
        --x;
        isfan[x] = 1;
    }
    for(int i = 0; i < 1 << N; ++i){
        for(int j = 0; j <= N; ++j){
            for(int x = 0; x < 2; ++x){
                for(int y = 0; y < 2; ++y){
                    DP[i][j][x][y] = -INF;
                }
            }
        }
    }
    for(int j = 1; j <= N; ++j){
        for(int i = 0; i + (1 << j) - 1 < (1 << N); i += (1 << j)){
            if(j == 1){
                DP[i][j][isfan[i]][isfan[i + 1]] = (isfan[i] || isfan[i + 1]);
                DP[i][j][isfan[i + 1]][isfan[i]] = (isfan[i] || isfan[i + 1]);
                continue;
            }
            for(int lu = 0; lu < 2; ++lu){
                for(int ld = 0; ld < 2; ++ld){
                    for(int ru = 0; ru < 2; ++ru){
                        for(int rd = 0; rd < 2; ++rd){
                            int val = DP[i][j - 1][lu][ld] + DP[i + (1 << (j - 1))][j - 1][ru][rd];
                            if(lu || ru)++val; // winner for upper when merge
                            if(ld || rd)++val; // winner for lower when merge
                            // say lu wins 
                            DP[i][j][lu][ru] = max(DP[i][j][lu][ru] , val + max((ru || ld) , (ru || rd)));
                            DP[i][j][lu][ld] = max(DP[i][j][lu][ld] , val + (ru || ld));
                            DP[i][j][lu][rd] = max(DP[i][j][lu][rd] , val + (ru || rd));
                            // say ru wins 
                            DP[i][j][ru][lu] = max(DP[i][j][ru][lu] , val + max((lu || ld) , (lu || rd)));
                            DP[i][j][ru][ld] = max(DP[i][j][ru][ld] , val + (lu || ld));
                            DP[i][j][ru][rd] = max(DP[i][j][ru][rd] , val + (lu || rd));
                        }
                    }
                }
            }
        }
    }
    int ans = 0;
    for(int x = 0; x < 2; ++x){
        for(int y = 0; y < 2; ++y){
            ans = max(ans , DP[0][N][x][y] + (x || y));
        }
    }
    printf("%d\n" , ans);
}