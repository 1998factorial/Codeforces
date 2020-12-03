#include <bits/stdc++.h>
using namespace std;

int DP[105][105][2] , a[105];

int solve(int i , int j , int lag){
    int& ret = DP[i][j][lag];
    if(~ret)return ret;
    if(i == j){
        ret = 1; return ret; // we have 1 now
    }
    ret = 0;
    if(lag){
        ret |= !solve(i , j , 0);
    }
    int one = 0;
    for(int k = i; k <= j; ++k){
        if(a[k] == 1)one = 1;
        if(k == i && a[k] < a[k + 1])continue;
        if(k == j && a[k] < a[k - 1])continue;
        if(k != i && k != j && (a[k] < a[k + 1] || a[k] < a[k - 1]))continue;
        if(one){
            int p = (j - k) & 1;
            ret |= !solve(i , k - 1 , lag ^ p);
        }
        else{
            int p = (k - i) & 1;
            ret |= !solve(k + 1 , j , lag ^ p);
        }
    }
    printf("DP[%d][%d][%d] = %d\n" , i , j , lag , ret);
    return ret;
}

int main(){
    int t;
    scanf("%d" , &t);
    while(t--){
        int N;
        scanf("%d" , &N);
        memset(DP , -1 , sizeof(DP));
        for(int i = 1; i <= N; ++i){
            scanf("%d" , &a[i]);
        }
        if(solve(1 , N , 0)){
            printf("Alice\n");
        }
        else{
            printf("Bob\n");
        }
    }
}