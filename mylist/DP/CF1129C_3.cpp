/*
    DP[l][r] = ans for s[l..r]
    ans for i is sum{sum{DP[y][x] , 1 <= y <= x} , 1 <= x <= i}
    minus the overcounted part , to avoid overcount, we let Min x to be the 
    the longest common suffix of s[...i] and some s[...k] , k <= i
*/
#include <bits/stdc++.h>
#define ID if(1)
#define ll long long 
using namespace std;

const ll MOD = 1e9 + 7;
bool mask[16];
int a[3005];
int LCS[3005][3005];
ll DP[3005][3005];
int N;

int main(){
    int i , j , k;
    scanf("%d" , &N);
    mask[3] = mask[5] = mask[14] = mask[15] = 1;
    for(i = 1; i <= N; ++i)scanf("%d" , &a[i]);
    for(i = 1; i <= N; ++i){
        for(j = 1; j <= i; ++j){
            if(a[i] == a[j]){
                LCS[i][j] = 1 + LCS[i - 1][j - 1];
                printf("LCS[%d][%d] = %d\n" , i , j , LCS[i][j]);
            }
        }
    }
    for(i = 1; i <= N; ++i)DP[i][i - 1] = 1;
    for(i = 1; i <= N; ++i){
        for(j = i; j <= N; ++j){
            if(i == j)DP[i][j] = 1;
            else if(i == j - 1)DP[i][j] = 2;
            else if(i == j - 2)DP[i][j] = 4;
            else{
                ll val = 0;
                int mk;
                for(k = 1; k <= 3; ++k)val += DP[i][j - k] , val %= MOD;
                for(k = 0; k < 3; ++k)mk += (a[j - k] << k);
                if(!mask[mk])val += DP[i][j - 4] , val %= MOD;
                DP[i][j] = val;
            }
            ID printf("DP[%d][%d] = %lld\n" , i , j , DP[i][j]);
        }
    }
    ll ret = 0;
}


