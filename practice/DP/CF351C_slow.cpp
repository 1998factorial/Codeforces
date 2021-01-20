#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll INF = 1e18;
int N , M , a[20] , b[20];
ll DP[2][50];
// key : at any moment, #l - #r <= 2N, else we can always swap one l with one r after this range

int main(){
    scanf("%d %d" , &N , &M);
    for(int i = 0; i < N; ++i){
        scanf("%d" , &a[i]);
    }
    for(int i = 0; i < N; ++i){
        scanf("%d" , &b[i]);
    }
    for(int j = 0; j <= 2 * N; ++j)DP[0][j] = INF;
    DP[0][0] = 0;
    for(int i = 0; i < N * M; ++i){
        int ci = i & 1 , ni = (i + 1) & 1;
        for(int j = 0; j <= 2 * N; ++j){
            DP[ni][j] = INF;
        }
        for(int j = 0; j <= 2 * N; ++j){
            // use (
            if(j + 1 <= 2 * N){
                DP[ni][j + 1] = min(DP[ni][j + 1] , DP[ci][j] + a[i % N]);
            }
            // use )
            if(j - 1 >= 0){
                DP[ni][j - 1] = min(DP[ni][j - 1] , DP[ci][j] + b[i % N]);
            }
        }
    }
    printf("%lld\n" , DP[(N * M) & 1][0]);
}