#include <bits/stdc++.h>
using namespace std;

int DP[500][500];
int N , K;

int main(){
    cin >> N >> K;
    for(int i = 0; i <= N; ++i)DP[i][0] = 1;
    for(int i = 1; i <= N; ++i){
        for(int j = 1; j <= K; ++j){
            DP[i][j] += DP[i - 1][j];
            DP[i][j] += DP[i - 1][j - 1];
            if(i - 2 >= 0)DP[i][j] += DP[i - 2][j - 1];
        }
    }
    for(int i = 1; i <= K; ++i){
        printf("%d " , DP[N][i]);
    }
    printf("\n");
}