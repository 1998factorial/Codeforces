#include <bits/stdc++.h>
#define ID if(0)
using namespace std;
typedef long long ll;
// count # of x + y = x ^ y is the same as count # x & y = 0
// we can not have (1 , 1) on any bit position
// DP[i][l1][r1][l2][r2] = # of ways for choosing (x , y), st , 
// l1 => x[...i] == l , !l1 => x[...i] > l
// r1 => x[...i] == r , !r1 => x[...i] < r
// from highest bit to lowest
// similar for y
ll DP[35][2][2][2][2];

int main(){
    int t;
    scanf("%d" , &t);
    while(t--){
        int l , r;
        scanf("%d%d" , &l , &r);
        memset(DP , 0 , sizeof(DP));
        DP[31][1][1][1][1] = 1;
        for(int i = 31; i >= 1; --i){
            for(int l1 : {0 , 1}){
                for(int r1 : {0 , 1}){
                    for(int l2 : {0 , 1}){
                        for(int r2 : {0 , 1}){
                            for(int x : {0 , 1 }){
                                for(int y : {0 , 1}){
                                    if(x && y)continue; // skip (1 , 1)
                                    if(l1 && x < (l >> (i - 1) & 1))continue;
                                    if(r1 && x > (r >> (i - 1) & 1))continue;
                                    if(l2 && y < (l >> (i - 1) & 1))continue;
                                    if(r2 && y > (r >> (i - 1) & 1))continue;
                                    int nl1 = l1 && x == (l >> (i - 1) & 1);
                                    int nr1 = r1 && x == (r >> (i - 1) & 1);
                                    int nl2 = l2 && y == (l >> (i - 1) & 1);
                                    int nr2 = r2 && y == (r >> (i - 1) & 1);
                                    DP[i - 1][nl1][nr1][nl2][nr2] += DP[i][l1][r1][l2][r2];
                                }
                            }
                        }
                    }
                }
            }
        }
        ll ret = 0;
        for(int l1 : {0 , 1}){
            for(int r1 : {0 , 1}){
                for(int l2 : {0 , 1}){
                    for(int r2 : {0 , 1}){
                        ret += DP[0][l1][r1][l2][r2];
                    }
                }
            }
        }
        printf("%lld\n" , ret);
    }
}