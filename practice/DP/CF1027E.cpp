/*
    Dynamic programming , counting , rating 2200
    Observation: once we fix the first row, the remaining rows are either the same as first row or the opposite
    To deal with the constraint that no rectangle of same color cells has area greater than or equal to K.
    Using the observation above, we can first, calculate the number of ways of having the maximal number of
    consecutive same color cells no more than  j for length i row.
    let this be DP[i][j]. then, the number of ways of having the maximal number of
    consecutive same color cells exactly j for length i row is DP[i][j + 1] - DP[i][j]
    let this be cnt[j]
    our answer is the sum of all cnt[i] * cnt[j] st i * j < K.
    since, the maximal consecutive color can be black or white, times it by 2 at the end
*/
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const ll mod = 998244353;
ll DP[505][505];
ll cnt[505];
int N , K;

int main(){
    cin >> N >> K;
    for(int i = 0; i <= N; ++i)DP[0][i] = 1;
    for(int i = 1; i <= N; ++i){
        for(int j = 1; j <= N; ++j){
            for(int k = i - 1; k >= max(0 , i - j); --k){
                DP[i][j] = (DP[i][j] + DP[k][j]) % mod;
            }
        }
    }
    for(int i = 1; i <= N; ++i){
        cnt[i] = (DP[N][i] - DP[N][i - 1] + mod) % mod;
    }
    ll ret = 0;
    for(int i = 1; i <= N; ++i){
        for(int j = 1; j <= N; ++j){
            if(i * j < K){
                ret = (ret + cnt[i] * cnt[j] % mod) % mod;
            }
        }
    }
    cout << ret * 2 % mod << endl;
}
