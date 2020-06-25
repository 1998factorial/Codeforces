/*
    Dynamic programming , rating 2100
    let DP[i] = min cost to encode s[1..i]
    DP[i] = min{DP[i - 1] + a , min{DP[l - 1] + b | s[l..i] is substring of s[1..l - 1]}}
    observe that DP[i + 1] >= DP[i] , as if DP[i + 1] = DP[i] + a > DP[i]
    if DP[i + 1] = DP[k - 1] + b = DP[i] , as if s[k..i + 1] is substring of s[1..k-1]
    then s[k..i] must be a substring of s[1..k-1].
    so we should pick smallest l , such that s[l..i] being a substring of s[1..l-1]
    to minimise the choice of DP[l - 1] + b.
    if s[j..i] is a substring of s[1..j-1] , then there must exist s[k..k+(i-j)] = s[j..i]
    in another word , s[1..k+(i-j)] and s[1..i] have common sufix of length i - j + 1
    so we can do : sufix[i][j] = length of longest common sufix of s[1..i] and s[1..j]
*/
#include <bits/stdc++.h>
using namespace std;

const int maxn = 5010;
int a , b , N;
char s[maxn];
int DP[maxn];
int sufix[maxn][maxn]; // sufix[i][j] = length of longest common sufix of s[1..i] and s[1..j]

int main(){
    scanf("%d %d %d" , &N , &a , &b);
    scanf("%s" , s + 1);
    for(int i = 1; i <= N; ++i){
        for(int j = 1; j < i; ++j){
            if(s[i] == s[j])sufix[j][i] = sufix[j - 1][i - 1] + 1;
        }
    }
    for(int i = 1; i <= N; ++i){
        DP[i] = DP[i - 1] + a;
        for(int j = 0; j < i; ++j){
            int len = sufix[j][i];
            if(len > 0){
                DP[i] = min(DP[i] , DP[max(i - len , j)] + b);
            }
        }
    }
    printf("%d\n" , DP[N]);
}
