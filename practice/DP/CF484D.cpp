/*
    Dynamic programming , rating 2400
    if the array is ascending / descending , the answer is just |a[1] - a[N]|
    so we can DP on this. The optimal solution is sum over some number of mountains
    DP[i][0] = maximal sum given a[i] is the maximal
    DP[i][1] = maximal sum given a[i] is the minimal
*/
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int maxn = 1e6 + 10;
ll a[maxn];
ll DP[maxn][2];
int N;

int main(){
    scanf("%d" , &N);
    for(int i = 1; i <= N; ++i){
        scanf("%lld" , &a[i]);
    }
    for(int i = 2; i <= N; ++i){
        if(a[i] >= a[i - 1]){
            DP[i][0] = max(DP[i - 1][0] + a[i] - a[i - 1] , DP[i - 1][1]);
            DP[i][1] = max(DP[i - 1][0] , DP[i - 1][1]);
        }
        else{
            DP[i][0] = max(DP[i - 1][0] , DP[i - 1][1]);
            DP[i][1] = max(DP[i - 1][0] , DP[i - 1][1] + a[i - 1] - a[i]);
        }
    }
    printf("%lld\n" , max(DP[N][0] , DP[N][1]));
}
