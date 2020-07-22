#include <bits/stdc++.h>
#define ID 0
using namespace std;

int N;
int a[100005];
int sum[100005];
int DP[100005];

int main(){
    int t; scanf("%d" , &t);
    while(t--){
        scanf("%d" , &N);
        for(int i = 1; i <= N; ++i)scanf("%d" , &a[i]);
        DP[N] = (a[N] > 0) ? 1 : 0;
        for(int i = N - 1; i >= 1; --i){
            if(a[i] == 0)DP[i] = DP[i + 1];
            else if(a[i] == 1)DP[i] = 1 - DP[i + 1];
            else{
                DP[i] = (1 - DP[i + 1]) || (DP[i + 1]);
            }
        }
        if(ID)for(int i = 1; i <= N; ++i)printf("DP[%d] = %d\n" , i , DP[i]);
        if(DP[1]){
            printf("First\n");
        }
        else{
            printf("Second\n");
        }
    }
}