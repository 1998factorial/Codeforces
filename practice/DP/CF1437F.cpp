#include <bits/stdc++.h>
#define MOD 998244353
using namespace std;
typedef long long ll;
int N , cnt[5005];
ll DP[5005][5005] , a[5005] , sum[5005][5005];
//DP[i][j] is # ways st y = a[i], and we have selected j people (including a[i])
int main(){
    scanf("%d" , &N);
    for(int i = 1; i <= N; ++i){
        scanf("%lld" , &a[i]);
    }
    sort(a + 1 , a + 1 + N);
    for(int i = 1; i <= N; ++i){
        int l = 1 , r = i - 1;
        while(l <= r){
            int mid = (l + r) >> 1;
            if(a[mid] * 2 <= a[i])cnt[i] = mid , l = mid + 1;
            else r = mid - 1;
        }
    }
    for(int i = 1; i <= N; ++i)DP[i][1] = 1 , sum[i][1] = sum[i - 1][1] + DP[i][1];
    for(int j = 2; j <= N; ++j){
        for(int i = 1; i <= N; ++i){
            if(cnt[i] - j + 1 >= 0){
                DP[i][j] += DP[i][j - 1] * (cnt[i] - j + 2) % MOD;
                if(DP[i][j] >= MOD)DP[i][j] -= MOD;
                DP[i][j] += sum[cnt[i]][j - 1];
                if(DP[i][j] >= MOD)DP[i][j] -= MOD;
            }
            sum[i][j] = sum[i - 1][j] + DP[i][j];
            if(sum[i][j] >= MOD)sum[i][j] -= MOD;
        }
    }
    printf("%lld\n" , DP[N][N]);
}