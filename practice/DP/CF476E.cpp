#include <bits/stdc++.h>
using namespace std;

char s[2005] , p[505];
int R[2005]; // R[i] = x, being the min y, st s[i..y] contains p
int N , M , DP[2005][2005]; // DP[i][j] = ans for s[1..i] if we delete j chars

int main(){
    scanf("%s" , s + 1);
    scanf("%s" , p + 1);
    N = strlen(s + 1);
    M = strlen(p + 1);
    for(int i = 1; i <= N; ++i){
        int k = 1 , j = i;
        for(; j <= N; ++j){
            if(s[j] == p[k]){
                ++k;
            }
            if(k > M){
                break;
            }
        }
        if(k > M)R[i] = j;
        else R[i] = -1;
    }
    memset(DP , -1 , sizeof(DP));
    DP[0][0] = 0;
    for(int i = 0; i < N; ++i){
        for(int j = 0; j <= N; ++j){
            if(~DP[i][j]){
                DP[i + 1][j + 1] = max(DP[i + 1][j + 1] , DP[i][j]);
                DP[i + 1][j] = max(DP[i + 1][j] , DP[i][j]);
                if(~R[i + 1]){
                    int len = R[i + 1] - (i + 1) + 1;
                    DP[R[i + 1]][j + len - M] = max(DP[R[i + 1]][j + len - M] , DP[i][j] + 1);
                }
            }
        }
    }
    for(int i = 0; i <= N; ++i){
        printf("%d " , DP[N][i]);
    }
    printf("\n");
}