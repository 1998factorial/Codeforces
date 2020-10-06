/*
    let DP[l][r] = the number of decoding way for s[l .. r]
    LCS[i][j] = longest common suffix for s[...i] and s[...j]
    ans for s[..i] is the ans for s[1...i-1] + some DP[x][i]
    where s[x..i] has not been counted before, so x < i - max(LCS[j][i]) where j < i
*/
#include <bits/stdc++.h>
#define MOD 1000000007
using namespace std;

int a[3005];
int DP[3005][3005];
int LCS[3005][3005];
int N;
bool mask[16];

int add(int x , int y){
    x += y;
    if(x >= MOD)x -= MOD;
    return x;
}

int main(){
    mask[3] = mask[5] = mask[14] = mask[15] = 1;
    int i , j , k;
    scanf("%d" , &N);
    for(i = 1; i <= N; ++i){
        scanf("%d" , &a[i]);
    }
    for(i = 1; i <= N; ++i){
        for(j = i; j >= 1; --j){
            if(a[i] == a[j])LCS[i][j] = LCS[i - 1][j - 1] + 1;
        }
    }
    for(i = 1; i <= N; ++i)DP[i][i - 1] = 1;
    for(i = 1; i <= N; ++i){
        for(j = i; j <= N; ++j){
            if(j - i + 1 <= 3)DP[i][j] = (1 << (j - i));
            else{
                int val = 0;
                for(k = 1; k <= 3; ++k){
                    val = add(val , DP[i][j - k]); // right point use length k word
                }
                int vmask = 0;
                for(k = 3; k >= 0; --k){
                    vmask = (vmask << 1) | a[j - k]; // see if right most length 4 word is bad
                }
                if(!mask[vmask]){
                    val = add(val , DP[i][j - 4]); // if not bad, we can use it
                }
                DP[i][j] = val;
            }
        }
    }
    int ret = 0;
    for(i = 1; i <= N; ++i){
        int max_lcs = 0;
        for(j = i - 1; j >= 0; --j){
            max_lcs = max(max_lcs , LCS[i][j] + 1);
        }
        for(j = max_lcs; j <= i; ++j){
            ret = add(ret , DP[i - j + 1][i]);
        }
        printf("%d\n" , ret);
    }
}