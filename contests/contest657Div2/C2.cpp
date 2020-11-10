#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int N , M;
ll a[100005] , b[100005];
ll DP[1005][1005];

ll solve(){
    DP[0][0] = 0;
    for(int i = 1; i <= M; ++i){
        for(int j = 0; j <= N; ++j){
            DP[i][j] = DP[i - 1][j];
            for(int x = 1; x <= N; ++x){
                if(j - x < 0)break;
                DP[i][j] = max(DP[i][j] , DP[i - 1][j - x] + a[i] + b[i] * (x - 1));
            }
        }
    }
    return DP[M][N];
}

int main(){
    int t; scanf("%d" , &t);
    while(t--){
        scanf("%d %d" , &N , &M);
        for(int i = 1; i <= M; ++i){
            scanf("%lld %lld" , &a[i] , &b[i]);
        }
        printf("%lld\n" , solve());
    }
}