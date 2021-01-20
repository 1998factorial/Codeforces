#include <bits/stdc++.h>
#define long double double
using namespace std;

double p[505] , ans[505];
int N , K;

int main(){
    scanf("%d %d" , &N , &K);
    for(int i = 0; i < N; ++i){
        scanf("%lF" , &p[i]);
        p[i] *= 100;
    }
    if(K == 1){
        for(int i = 1; i <= N; ++i)printf("100 ");
        printf("\n");
        return 0;
    }
    for(int i = 0; i < N; ++i){
        // calculate the expected score for ith monster
        //printf("for monster %d\n" , i);
        for(int j = 0; j <= N - K; ++j){
            // say there are j monster right before i will not be in pool
            //printf("for len = %d\n" , j);
            double v = 0 , pt = 1;
            for(int k = 0; k <= j; ++k){
                int id = ((i - k) % N + N) % N;
                //printf("id = %d " , id);
                v += p[id];
            }
            pt *= (double)K / N; // select ith monster
            pt *= (double)(K - 1) / (N - j - 1); // close the interval
            //printf("(%d / %d) , " , K , N);
            //printf("(%d / %d) , " , K - 1 , N - j - 1);
            for(int k = 1; k <= j; ++k){
                //printf("(%d / %d) , " , N - K - k + 1 , N - k);
                pt *= (double)(N - K - k + 1) / (N - k);
            }
            //printf("\n");
            //printf("pt = %lF\n" , pt);
            ans[i] += v * pt;
        }
    }
    for(int i = 0; i < N; ++i){
        printf("%.12lF " , ans[i] / 100.0);
    }
    printf("\n");
}   