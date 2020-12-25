#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int N;
ll W , B , X;
int cnt[1005];
ll DP[1005][10005] , cost[1005];
// DP[i][j] = maximal amount of mana if we are at tree i summoned j birds

int main(){
    scanf("%d %lld %lld %lld" , &N , &W , &B , &X);
    int sum = 0;
    for(int i = 1; i <= N; ++i){
        scanf("%d" , &cnt[i]);
        sum += cnt[i];
    }
    for(int i = 1; i <= N; ++i){
        scanf("%lld" , &cost[i]);
    }
    for(int i = 0; i <= N; ++i){
        for(int j = 0; j <= sum; ++j){
            DP[i][j] = -1;
        }
    }
    DP[0][0] = W;
    int ret = 0;
    for(int i = 0; i < N; ++i){
        for(int j = 0; j <= sum; ++j){
            if(DP[i][j] == -1)continue;
            ll cap = W + B * j;
            ll mana = min(DP[i][j] + (i > 0 ? X : 0) , cap);
            for(int k = 0; k <= cnt[i + 1]; ++k){
                if(mana < cost[i + 1] * k)break;
                DP[i + 1][j + k] = max(DP[i + 1][j + k] , mana - cost[i + 1] * k);
            }
        }
    }
    for(int i = 0; i <= sum; ++i){
        if(~DP[N][i]){
            ret = max(ret , i);
        }
    }
    printf("%d\n" , ret);
}