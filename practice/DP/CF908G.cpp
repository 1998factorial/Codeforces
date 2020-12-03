#include <bits/stdc++.h>
#define rep(i , a , b) for(int i = a; i <= b; ++i)
using namespace std;
// Hard DP , 2800
// S(k) = number that represents k, but digits are sorted
// eg. S(5) = 5 , S(50394) = 3459 , S(353535) = 333555
// compute sum{S(k) | 1 <= k <= X} % MOD
// X <= 1e700
typedef long long ll;
const ll MOD = 1e9 + 7;
char a[705];
int X[705];
int N;
ll DP[705][705][10][2];
// 111222333 = 111111111 + 111111 + 111
// 1234 = 1111 + 111 + 11 + 1
// 1...1 #(digits >= 9) + 1...1 #(digits >= 8) + .... + 1...1 #(digits >= 1)
// for each single number
// By this observation, it make sense to calculate the total sum by spliting to 
// (total contribution by digits >= 9) + (total contribution by digits >= 8) + ...
// if we fix digit d , the goal is to find the number of ways to make 
// valid number that have j digits >= d 
// DP[i][j][d][k] = # of ways to fill the first i digits 
// such that there are j digits >= d, k => same , !k => strictly less
// ans will be (DP[N][i][d][0] + DP[N][i][d][1]) * 11...11 (i ones)
// for all i <= N , d <= 9
int main(){
    scanf("%s" , a + 1);
    N = strlen(a + 1);
    rep(i , 1 , N)X[i] = a[i] - '0';
    rep(i , 0 , 9)DP[0][0][i][1] = 1; // base
    rep(d , 0 , 9){ // compute number of good numbers that has some number of digits >= d
        rep(i , 0 , N - 1){
            rep(j , 0 , i){
                rep(k , 0 , 1){
                    ll v = DP[i][j][d][k];
                    if(!v)continue;
                    rep(nd , 0 , 9){
                        if(k && nd > X[i + 1])continue;
                        int nk = k && nd == X[i + 1];
                        ll& nv = DP[i + 1][j + (nd >= d)][d][nk];
                        nv += v;
                        if(nv >= MOD)nv -= MOD;
                    }
                }
            }
        }
    }
    ll ret = 0;
    rep(d , 1 , 9){
        ll ones = 1;
        rep(i , 1 , N){ 
            ll v = (DP[N][i][d][0] + DP[N][i][d][1]) % MOD;
            ret += v * ones % MOD;
            if(ret >= MOD)ret -= MOD;
            ones = (ones * 10 % MOD + 1) % MOD;
        }
    }
    printf("%lld\n" , ret);
}