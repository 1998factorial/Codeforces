#include <bits/stdc++.h>
#define ID if(0)
using namespace std;
typedef long long ll;
const ll mod = 1e9 + 7;
ll DP[2005][2005];
ll cnt[2005];
int P[2005] , Q[2005];
int N;
ll sub(ll x , ll y){
    return (x - y + mod) % mod;
}
ll add(ll x , ll y){
    return (x + y) % mod;
}
ll mul(ll x , ll y){
    return x * y % mod;
}
int main(){
    int i , j , k;
    scanf("%d" , &N);
    for(i = 1; i <= N; ++i)scanf("%d" , &P[i]);
    for(i = 1; i <= N; ++i)scanf("%d" , &Q[i]);
    cnt[0] = 1;
    cnt[1] = 1;
    for(i = 2; i <= N; ++i){
        for(j = 0; j <= i - 1; ++j){
            cnt[i] = add(cnt[i] , mul(cnt[j] , cnt[i - j - 1]));
        }
    }
    DP[0][0] = 1;
    for(i = 1; i <= N; ++i)DP[0][i] = DP[i][0] = 1;
    for(i = 1; i <= N; ++i){
        for(j = 1; j <= N; ++j){
            DP[i][j] = add(DP[i - 1][j] , DP[i][j - 1]);
            for(k = 1; P[i - k + 1] == Q[j - k + 1] && k <= min(i , j); ++k){
                DP[i][j] = sub(DP[i][j] , mul(DP[i - k][j - k] , cnt[k - 1]));
            }
        }
    }
    printf("%lld\n" , DP[N][N]);
}