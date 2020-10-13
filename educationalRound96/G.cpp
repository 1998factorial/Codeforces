/*
    we solve this problem layer by layer
    DP[s] = minimal cost to assign vertex in s
    DP[s] = min{DP[ps] + sum(s \ ps)} , for all valid previous state ps
    
*/
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll INF = 1e18;
ll sum[1 << 20] , DP[1 << 20] , val[20];
int N , M , pre[20] , ans[20] , incoming[1 << 20] , prestate[1 << 20];

int main(){
    int i , j , k;
    scanf("%d%d" , &N , &M);
    for(i = 0; i < M; ++i){
        int x , y , w;
        scanf("%d%d%d" , &x , &y , &w);
        --x;
        --y;
        pre[y] |= (1 << x);
        val[x] += w;
        val[y] -= w;
    }
    for(i = 0; i < (1 << N); ++i){
        for(j = 0; j < N; ++j){
            if(i & (1 << j)){
                sum[i] += val[j];
                incoming[i] |= pre[j];
            }
        }
    }
    for(i = 0; i < (1 << N); ++i){
        DP[i] = INF;
        if(!incoming[i]){
            DP[i] = 0;
            prestate[i] = i;
        }
        else{
            for(j = i; j; j = (j - 1) & i){
                int pi = i ^ j;
                if(incoming[j] == (incoming[j] & pi)){ // if previous layer are all in pi
                    if(DP[i] > DP[pi] + sum[pi]){
                        DP[i] = DP[pi] + sum[pi];
                        prestate[i] = pi;
                    }                    
                }
            }
        }
    }
    int s = (1 << N) - 1;
    while(prestate[s] != s){
        for(i = 0; i < N; ++i){
            if(prestate[s] & (1 << i)){
                ++ans[i];
            }
        }
        s = prestate[s];
    }
    for(int i = 0; i < N; ++i){
        printf("%d " , ans[i] + 1);
    }
    printf("\n");
}