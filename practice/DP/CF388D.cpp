/*
    Dynamic programming [digit DP] , linear bases , rating 2700

    Each perfect set correspond to a unique linear base. (We can check this by doing Gaussian elimination) So, counting the number of perfect set that contains
    no integer greater than K is the same as counting the linear bases where the maximal xor combinations is no
    more than K.
    Sources on linear bases: https://oi.men.ci/linear-basis-notes/
    we can choose bases from highest bit to lowest bit, assuming that we have reversed the binary representation of K
    DP[i][j][k] = # of ways to select j bases from the highest i bits k = 1 if the maximal xor value matches the
    prefix of K (assuming reversed) , k = 0, if maximal xor value is smaller.

    consider ith highest bit, where maximal xor is smaller than prefix of K.
    we can either add the ith bit into base , or we do not add it, so that the previous j chosen bits can have 0 or 1
    on the ith bit. DP[i][j][0] = DP[i - 1][j][0] * (1 << j) + DP[i - 1][j - 1][0]

    if the maximal xor is equal to the prefix of K.
    if a[i] = 0, we can not make it the base, because if we xor the ith bit, we will go over K
    so we can select an even number of bases from the determined j bases, giving C(j , 0) + C(j , 2) + ...
    which is (1 << (j - 1)), 1 if j is 0
    if a[i] = 1, we can choose ith bit to be the base, which gives transit to DP[i][j][1] += DP[i - 1][j - 1][1]
    if we do not, we can either select an even number of bases from the j ones, which is DP[i][j][0] += DP[i - 1][j - 1][1] * (1 << (j - 1))
    or, we select an odd number of bases, which is DP[i][j][1] += DP[i - 1][j][1] * (1 << (j - 1)), coeficient is 0 if j == 0.
    our answer is sum of all DP[N][i][0] + DP[N][i][1] , 0 <= i <= N
*/
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const ll mod = 1e9 + 7;
const int maxn = 35;

ll DP[maxn][maxn][2];
int a[maxn];
int N = 0;
ll K;

int main(){
    cin >> K;
    if(!K)a[++N] = 0;
    while(K){
        a[++N] = K % 2;
        K /= 2;
    }
    reverse(a + 1 , a + N + 1);
    DP[0][0][1] = 1;
    for(int i = 1; i <= N; ++i){
        for(int j = 0; j <= i; ++j){
            // transit to strict less than prefix
            DP[i][j][0] = (DP[i][j][0] + (1ll << j) * DP[i - 1][j][0] % mod) % mod; // do not choose ith bit to be base
            if(j) DP[i][j][0] = (DP[i][j][0] + DP[i - 1][j - 1][0]) % mod; // we choose ith bit to be base
            // transit to equal prefix
            ll odd = (j > 0) ? (1ll << (j - 1)) % mod : 0;
            ll even = (j > 0) ? (1ll << (j - 1)) % mod : 1;
            if(a[i] == 0){
                DP[i][j][1] = (DP[i][j][1] + even * DP[i - 1][j][1] % mod) % mod; // we can not let xor sum on ith bit to be 1
            }
            else{
                if(j) DP[i][j][1] = (DP[i][j][1] + DP[i - 1][j - 1][1]) % mod; // we choose ith bit as base
                DP[i][j][1] = (DP[i][j][1] + odd * DP[i - 1][j][1] % mod) % mod; // if we choose odd number of bases to have 1 on ith bit, then the flag is still on, as ith bit xor to 1
                DP[i][j][0] = (DP[i][j][0] + even * DP[i - 1][j][1] % mod) % mod; // if we choose even number of bases to have 1 on ith bit, then the flag is off, as ith bit xor to 0
            }
        }
    }
    ll ret = 0;
    for(int i = 0; i <= N; ++i){
        ret = (ret + (DP[N][i][0] + DP[N][i][1]) % mod) % mod;
    }
    cout << ret << endl;
}
