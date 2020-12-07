#include <bits/stdc++.h>
#define rep(i , a , b) for(int i = a; i <= b; ++i)
#define rrep(i , a , b) for(int i = a; i >= b; --i)
using namespace std;
typedef long long ll;
int N , K;
int sz[3005];
int a[3005][3005];
ll sum[3005][3005] , DP[3005];

// Key: in the optimal solution, there is at most one array that is taken partially
// all other arrays are taken completely

int main(){
    scanf("%d %d" , &N , &K);
    rep(i , 1 , N){
        scanf("%d" , &sz[i]);
        rep(j , 1 , sz[i]){
            int x; scanf("%d" , &x);
            if(j <= K)a[i][j] = x , sum[i][j] = sum[i][j - 1] + x;
        }
        sz[i] = min(sz[i] , K);
    }
    ll ret = 0;
    rep(i , 1 , N){
        rep(j , 0 , K)DP[j] = 0;
        rep(j , 1 , N){
            if(i != j){
                rrep(k , K , sz[j]){
                    DP[k] = max(DP[k] , DP[k - sz[j]] + sum[j][sz[j]]);
                }
            }
        }
        rep(k , 1 , sz[i]){
            DP[K] = max(DP[K] , DP[K - k] + sum[i][k]);
        }
        ret = max(ret , DP[K]);
    }
    printf("%lld\n" , ret);
}