/*
    Dynamic programming , rating 2700
    partition a[1..N] into K contigous & disjoint subarrays
    record their array sum as s[1..K] , where s[i] = a[l[i]] + ... + a[r[i]]
    goal is to maximise |s[1] - s[2]| + .. + |s[K - 1] - s[K]|
    Observation: if we present any K subarray sums into a histogram , we should see that
    only those "peak" and "trough" will contribute to the solution
    (the solution looks like : peak - 2 * trough + 2 * peak - 2 * trough + 2 * peak - trough)
    DP[i][j][k] = the maximal answer when we partition the first i elements into j subarrays where
    the last subarry is in state k.
    state k :
    00 [min .. max) first
    01 [min .. max] middle
    10 [max .. min) first
    11 [max .. min) middle
*/
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int maxn = 30010;
const ll INF = 1e18;
int N , K;
ll a[maxn];
ll DP[maxn][205][2][2];

int main(){
    scanf("%d %d" , &N , &K);
    for(int i = 1; i <= N; ++i){
        scanf("%lld" , &a[i]);
    }
    for(int j = 1; j <= K; ++j){
        for(int x : {0 , 1}){
            for(int y : {0 , 1}){
                DP[0][j][x][y] = -INF;
            }
        }
    }
    for(int i = 1; i <= N; ++i){
        for(int j = 1; j <= K; ++j){
            ll c = (j > 1 && j < K) ? 2 : 1;
            DP[i][j][0][0] = max(DP[i - 1][j][0][0] , DP[i - 1][j - 1][1][1]) - c * a[i];
            DP[i][j][1][0] = max(DP[i - 1][j][1][0] , DP[i - 1][j - 1][0][1]) + c * a[i];
            DP[i][j][0][1] = max(DP[i - 1][j][0][1] , DP[i][j][0][0]);
            DP[i][j][1][1] = max(DP[i - 1][j][1][1] , DP[i][j][1][0]);
            if(c > 1){
                DP[i][j][0][1] = max(DP[i][j][0][1] , DP[i - 1][j - 1][0][1]);
                DP[i][j][1][1] = max(DP[i][j][1][1] , DP[i - 1][j - 1][1][1]);
            }
        }
    }
    printf("%lld\n" , max(DP[N][K][0][1] , DP[N][K][1][1]));
}
