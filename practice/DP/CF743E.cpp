#include <bits/stdc++.h>
#define ID if(0)
using namespace std;
int N;
int a[1005] , cnt[1005][8] , DP[1 << 8][1005];

int main(){
    scanf("%d" , &N);
    for(int i = 1; i <= N; ++i){
        scanf("%d" , &a[i]);
        --a[i];
        ++cnt[i][a[i]];
    }
    for(int i = 1; i <= N; ++i){
        for(int j = 0; j < 8; ++j){
            cnt[i][j] += cnt[i - 1][j];
        }
    }
    int ans = 0 , l = 0 , r = N / 8;
    while(l <= r){ // Bsearch len
        int len = (l + r) >> 1;
        // DP[mask][i] = maximal number of k , k <= 8 st we have k colors with len + 1
        memset(DP , -1 , sizeof(DP));
        DP[0][0] = 0;
        for(int i = 0; i < N; ++i){
            for(int mask = 0; mask < (1 << 8); ++mask){
                for(int j = 0; j < 8; ++j){
                    if(mask & (1 << j) || DP[mask][i] == -1)continue;
                    int ni = -1 , s = i , e = N , nmask = mask | (1 << j);
                    // find len
                    while(s <= e){
                        int mid = (s + e) >> 1;
                        if(cnt[mid][j] - cnt[i][j] >= len){
                            ni = mid;
                            e = mid - 1;
                        }
                        else s = mid + 1;
                    }
                    if(~ni)DP[nmask][ni] = max(DP[nmask][ni] , DP[mask][i]);
                    // find len + 1
                    ni = -1 , s = i , e = N;
                    while(s <= e){
                        int mid = (s + e) >> 1;
                        if(cnt[mid][j] - cnt[i][j] >= len + 1){
                            ni = mid;
                            e = mid - 1;
                        }
                        else s = mid + 1;
                    }
                    if(~ni)DP[nmask][ni] = max(DP[nmask][ni] , DP[mask][i] + 1);
                }
            }
        }
        int best = -1;
        for(int i = 1; i <= N; ++i){
            best = max(best , DP[(1 << 8) - 1][i]);
        }   
        if(~best){
            ans = max(ans , len * 8 + best);
            l = len + 1;
        }
        else{
            r = len - 1;
        }
    }
    printf("%d\n" , ans);
}