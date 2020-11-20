#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll INF = 1e18;
int a[3005] , N , b[3005];
ll DP[3005][3005];

// min op to make sequence increasing seems hard
// min op to make sequence non-decreasing seems easier
// {a[i]}->{a[i]-i}
// DP[i][j] = min op to make sequence non-decreasing 
// if we make a[i] to be the jth smallest in array a

int main(){
    scanf("%d" , &N);
    for(int i = 1; i <= N; ++i)scanf("%d" , &a[i]) , a[i] -= i , b[i] = a[i];
    sort(b + 1 , b + 1 + N);
    for(int i = 0; i <= N; ++i){
        for(int j = 0; j <= N; ++j){
            DP[i][j] = INF;
        }
    }
    DP[0][1] = 0;
    for(int i = 1; i <= N; ++i){
        ll mv = INF;
        for(int j = 1; j <= N; ++j){
            mv = min(mv , DP[i - 1][j]);
            DP[i][j] = min(DP[i][j] , mv + abs(a[i] - b[j]));
        }
    }
    ll ret = INF;
    for(int i = 1; i <= N; ++i){
        ret = min(ret , DP[N][i]);
    }
    printf("%lld\n" , ret);
}