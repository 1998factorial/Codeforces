#include <bits/stdc++.h>
using namespace std;

int N , M , K;
int l[2005] , r[2005];
int cost[2005][2005];

int inter(int l1 , int r1 , int l2 , int r2){
    int v = min(r1 , r2) - max(l1 , l2) + 1;
    return v < 0 ? 0 : v;
}

int main(){
    scanf("%d %d %d" , &N , &M , &K);
    for(int i = 1; i <= M; ++i){
        scanf("%d %d" , &l[i] , &r[i]);
    }   
    for(int s = 1; s + K - 1 <= N; ++s){
        for(int i = 1; i <= M; ++i){
            cost[s][i] = inter(s , s + K - 1 , l[i] , r[i]);
        }
    }
    int ret = 0;
    for(int s1 = 1; s1 + K - 1 <= N; ++s1){
        for(int s2 = 1; s2 + K - 1 <= N; ++s2){
            int v = 0;
            for(int i = 1; i <= N; ++i){
                v += max(cost[s1][i] , cost[s2][i]);
            }
            ret = max(ret , v);
        }
    }
    printf("%d\n" , ret);
}