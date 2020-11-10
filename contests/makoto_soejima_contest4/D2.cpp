/*
    our state is DP[i][j] = number of distinct array we can make using P[1..i] and Q[1..j]
    DP[i][j] = DP[i - 1][j] + DP[i][j - 1] - duplication
    we observe that only good sequence like 123123 will be counted twice , as we can change the 
    order of our selection (P then Q or Q then P)
    so we need to find all common suffix of P[1..i] and Q[1..j] that are good sequence
    and subtract #(good sequence of length k permutation) * DP[i - k][j - k]
    to count the number of good sequence of length k, we can let G[i][j] = the number of 
    good sequence of length 2 * i and the first i is placed at position j
    G[i][j] = 0 if j > 2 * i - 2 , as we will have suffix = ".... i , i" , which is not a 
    good sequence. (as we don't want to deal with another sequence made by 2 permutations of 1..i-1)
    G[i][j] = sum{G[i - 1][k] | k < j}
    cnt[i] = sum{G[i][j] | j <= 2 * i - 2}
    DP[i][j] = DP[i - 1 ][j] + DP[i][j - 1] - sum{cnt[k] * DP[i - k][j - k] | length k common suffix}
    time : O(sum{sum{common_suffix(P[1..i] , Q[1..j])}}) = O(N * N)
*/
#include <bits/stdc++.h>
#define ID if(0)
using namespace std;
typedef long long ll;
const ll mod = 1e9 + 7;
ll DP[2005][2005];
ll cnt[2005] , G[2005][4010] , sum[4010];
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
    G[1][1] = cnt[1] = 1;
    for(i = 2; i <= N; ++i){
        for(j = 1; j <= 2 * i - 2; ++j)sum[j] = 0;
        for(j = 1; j <= 2 * i - 2; ++j){
            sum[j] = sum[j - 1];
            sum[j] = add(sum[j] , G[i - 1][j]);
            G[i][j] = add(G[i][j] , sum[j - 1]);
            cnt[i] = add(cnt[i] , G[i][j]);
        }
    }
    DP[0][0] = 1;
    for(i = 1; i <= N; ++i)DP[0][i] = DP[i][0] = 1;
    for(i = 1; i <= N; ++i){
        for(j = 1; j <= N; ++j){
            DP[i][j] = add(DP[i - 1][j] , DP[i][j - 1]);
            for(k = 1; P[i - k + 1] == Q[j - k + 1] && k <= min(i , j); ++k){
                DP[i][j] = sub(DP[i][j] , mul(DP[i - k][j - k] , cnt[k]));
            }
        }
    }
    printf("%lld\n" , DP[N][N]);
}