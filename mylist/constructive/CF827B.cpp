/*
    Constructive
    optimal structure: 1 at center and we have k branches coming out from 1
    and what we need to do is just to connect each point to the branch that it
    is supposed to be connected to in a rotational manner
*/
#include <bits/stdc++.h>
using namespace std;

int N , K;

int main(){
    scanf("%d %d", &N , &K);
    --N; // excluding center when calculating length
    int min_len = N / K; // K branches
    int max_len = (N % K) ? min_len + 1 : min_len;
    int ans = (N % K >= 2) ? 2 * max_len : max_len + min_len;
    printf("%d\n" , ans);
    ++N;
    for(int i = 2; i <= K + 1; ++i){
        printf("%d %d\n" , 1 , i);
    }
    for(int i = K + 2; i <= N; ++i){
        printf("%d %d\n" , i , i - K);
    }
}
