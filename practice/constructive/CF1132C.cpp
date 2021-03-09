#include <bits/stdc++.h>
using namespace std;

int N , Q;
array<int , 2> qs[5005];
int cover[5005][5005] , sum[5005];

int main(){
    scanf("%d %d" , &N , &Q);
    for(int i = 1; i <= Q; ++i){
        scanf("%d %d" , &qs[i][0] , &qs[i][1]);
    }
    int ans = 0;
    for(int i = 1; i <= Q; ++i){
        for(int j = 1; j <= Q; ++j){
            if(i == j)continue;
            ++cover[i][qs[j][0]];
            --cover[i][qs[j][1] + 1];
        }
        for(int j = 1; j <= N; ++j){
            cover[i][j] += cover[i][j - 1];
        }
        int tot = 0;
        for(int j = 1; j <= N; ++j){
            if(cover[i][j]){
                ++tot;
            }
        }
        for(int j = 1; j <= N; ++j){
            sum[j] = 0;
        }
        for(int j = 1; j <= N; ++j){
            sum[j] += sum[j - 1] + (cover[i][j] == 1);
        }
        int mn = tot;
        for(int j = 1; j <= Q; ++j){
            if(i == j)continue;
            mn = min(mn , sum[qs[j][1]] - sum[qs[j][0] - 1]);
        }
        ans = max(ans , tot - mn);
    }
    printf("%d\n" , ans);
}