/*
    Constructive , recursion
    lets see what happen if we use the answer for K - 1 on K
    let the matrix that solves K - 1 be A. (2 ^ (K - 1) by 2 ^ (K - 1))
    Make 4 copies of A and paste them into a matrix that is (2 ^ K by 2 ^ K)
    Negate the bottom right A, and it is easy to see that this resulting matrix is
    a good matrix
*/
#include <bits/stdc++.h>
using namespace std;

int K;
int ans[(1 << 9) + 10][(1 << 9) + 10];

void solve(int len , int tx , int ty , int val){
    if(len == 1){
        ans[tx][ty] = val;
    }
    else{
        int nlen = len >> 1;
        solve(nlen , tx , ty , val);
        solve(nlen , tx , ty + nlen , val);
        solve(nlen , tx + nlen , ty , val);
        solve(nlen , tx + nlen , ty + nlen , -val);
    }
}

int main(){
    scanf("%d" , &K);
    solve((1 << K) , 1 , 1 , 1);
    for(int i = 1; i <= (1 << K); ++i){
        for(int j = 1; j <= (1 << K); ++j){
            if(ans[i][j] == 1){
                printf("+");
            }
            else{
                printf("*");
            }
        }
        printf("\n");
    }
}
