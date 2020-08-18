/*
    This is O(N ^ 2 + Q * N ^ 2) bruteforce solution 
*/
#include <bits/stdc++.h>
using namespace std;

const int maxn = 500 + 10;
int N , X , Y , Q;
int a[maxn];
int C[maxn][maxn];

int main(){
    scanf("%d %d %d" , &N , &X , &Y);
    for(int i = 0; i <= N; ++i){
        scanf("%d" , &a[i]);
    }
    for(int i = 0; i <= N; ++i){
        for(int j = i + 1; j <= N; ++j){
            C[i][j] = 2 * (a[j] - a[i] + Y);
        }
    }
    scanf("%d" , &Q);
    while(Q--){
        int l; 
        scanf("%d" , &l);
        int ret = -1;
        for(int i = 0; i <= N; ++i){
            if(2 * a[i] > l)break;
            for(int j = i - 1; j >= 0; --j){
                if(l % C[j][i] == 0){
                    ret = max(ret , C[j][i]);
                }
            }
        }
        printf("%d " , ret);
    }
    printf("\n");
}