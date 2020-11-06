#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll INF = 1e18;
ll a[105][105] , DP[105][105] , b[105][105];
int N , M;

int main(){
    int t , i , j , k , l;
    scanf("%d" , &t);
    while(t--){
        scanf("%d %d" , &N , &M);
        for(i = 1; i <= N; ++i){
            for(j = 1; j <= M; ++j){
                scanf("%lld" , &a[i][j]);
                b[i][j] = a[i][j] - i - j + 2;
            }
        }
        ll ret = INF;
        for(i = 1; i <= N; ++i){
            for(j = 1; j <= M; ++j){
                ll x = b[i][j];
                for(k = 0; k <= N; ++k){
                    for(l = 0; l <= M; ++l){
                        DP[k][l] = INF;
                    }
                }
                DP[0][1] = DP[1][0] = 0;
                for(k = 1; k <= N; ++k){
                    for(l = 1; l <= M; ++l){
                        if(b[k][l] - x >= 0)DP[k][l] = min(DP[k - 1][l] , DP[k][l - 1]) + b[k][l] - x;
                    }
                }
                ret = min(ret , DP[N][M]);
            }
        }
        printf("%lld\n" , ret);
    }
}