/*
    Dynamic programming , counting rating 2500

    in optimal solution, we should place as many 2 ^ x * 3 ^ y to the beginning as possible
    if we place f * 5 , f, it is suboptimal as we could replace f * 2 * 2 , f * 2 , f
    which will make 1 more distinct GCD. Also, note that the power of 3 will not excceed 2 as it is always
    better to replace 9 with 8, which will give us one extra distinct GCD.
    Therefore, we should either start with 2 ^ k or 2 ^ (k - 1) * 3 (if 2 ^ (k - 1) * 3 <= N)
    where 2 ^ k is the largest powers of 2 that does not
    excceed N.
    Then, how will our gcd change? firstly, from previous argument, our gcd must be in the form of
    2 ^ x * 3 ^ y, and in order to maximise the number of distinct gcds, we note that x + y is non increasing.
    So, we can count the number of ways to put the first i elements such that g[i] = 2 ^ x * 3 ^ y.
    let DP[i][x][y] be such. our answer will be DP[N][0][0].
    note that each time, we transit from (x , y) to one of the 3 possible outcomes namely , (x , y) , (x - 1 , y) , (x , y - 1)
    DP[i][x][y] * #[x in [1 , N] that is divisible by 2 ^ x * 3 ^ y but not selected prior] -> DP[i + 1][x][y]
    which is just DP[i][x][y] * (N / (2 ^ x * 3 ^ y) - i) , as all previous selected i numbers must be divisible by 2 ^ x * 3 ^ y.
    DP[i][x][y] * #[x in [1 , N] that is divisible by 2 ^ (x - 1) * 3 ^ y but not divisible by 2 ^ x * 3 ^ y ] -> DP[i + 1][x - 1][y]
    which is just DP[i][x][y] * (N / (2 ^ x * 3 ^ y) - N / (2 ^ (x - 1) * 3 ^ y))
    and another transition is similar
*/

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll mod = 1e9 + 7;
const int maxn = 1e6 + 10;
int DP[maxn][20][2];
int cnt[20][2];
int N;

int count(int x , int y){ // returns #[x in [1 , N] that is a multiple of 2 ^ x * 3 ^ y]
    int two = (1 << x);
    int three = (y == 0) ? 1 : 3;
    return N / (two * three);
}

int main(){
    scanf("%d" , &N);
    int lim = log2(N);
    for(int x = 0; x <= lim; ++x){
        for(int y : {0 , 1}){
            cnt[x][y] = count(x , y);
        }
    }
    DP[1][lim][0] = 1;
    if((1 << (lim - 1)) * 3 <= N)DP[1][lim - 1][1] = 1;
    for(int i = 1; i < N; ++i){
        for(int x = 0; x <= lim; ++x){
            for(int y : {0 , 1}){
                // (x , y) -> (x , y)
                DP[i + 1][x][y] = ((ll)DP[i + 1][x][y] + (ll)DP[i][x][y] * (cnt[x][y] - i)) % mod;
                // (x , y) -> (x - 1 , y)
                if(x)DP[i + 1][x - 1][y] = ((ll)DP[i + 1][x - 1][y] + (ll)DP[i][x][y] * (cnt[x - 1][y] - cnt[x][y])) % mod;
                // (x , y) -> (x , y - 1)
                if(y)DP[i + 1][x][y - 1] = ((ll)DP[i + 1][x][y - 1] + (ll)DP[i][x][y] * (cnt[x][y - 1] - cnt[x][y])) % mod;
            }
        }
    }
    printf("%d\n" , DP[N][0][0]);
}
