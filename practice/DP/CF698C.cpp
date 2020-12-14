#include <bits/stdc++.h>
using namespace std;

double p[20] , DP[1 << 20] , ans[20];
int N , K;

int main(){
    scanf("%d %d" , &N , &K);
    int nz = 0;
    for(int i = 0; i < N; ++i){
        scanf("%lf" , &p[i]);
        nz += p[i] == 0;
    }
    if(N - nz < K)K = N - nz;
    DP[0] = 1;
    for(int mask = 0; mask < (1 << N); ++mask){
        // backwards
        int nb = __builtin_popcount(mask);
        if(nb > K)continue;
        double np = 0;
        for(int i = 0; i < N; ++i){
            if((mask >> i & 1) == 0)np += p[i];
        }
        for(int i = 0; i < N; ++i){
            if((mask >> i & 1) == 0){
                DP[mask | (1 << i)] += DP[mask] * p[i] / np;
            }
        }
        if(nb == K){
            for(int i = 0; i < N; ++i){
                if(mask >> i & 1)ans[i] += DP[mask];
            }
        }
    }
    for(int i = 0; i < N; ++i){
        printf("%.10lf " , ans[i]);
    }
    printf("\n");
}