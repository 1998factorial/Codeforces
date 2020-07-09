/*
    Dynamic programming , rating 2400
    DP[i][l][r] = contribution of s[l..r] in F[i]
*/
#include <bits/stdc++.h>
#define ID 0
using namespace std;
typedef long long ll;

const ll mod = 1e9 + 7;
char s[105];
ll DP[105][105][105];
ll F[105];
int N , X;

ll qpow(ll x , int n){
    if(n <= 0)return 1;
    ll ret = qpow(x , n / 2);
    ret = ret * ret % mod;
    if(n & 1)ret = ret * x % mod;
    return ret;
}

int main(){
    cin >> N >> X;
    F[0] = F[1] = 1;
    for(int i = 2; i <= X; ++i){
        F[i] = (F[i - 1] + F[i - 2]) % (mod - 1);
    }
    cin >> (s + 1);
    for(int i = 1; i <= N; ++i){
        DP[s[i] - '0'][i][i] = 1;
    }
    if(ID)for(int i = 1; i <= N; ++i){
        for(int j = 0; j < 2; ++j)printf("DP[%d][%d][%d] = %lld\n" , j , i , i , DP[j][i][i]);
    }
    for(int x = 2; x <= X; ++x){
        for(int len = 1; len <= N; ++len){
            for(int l = 1; l + len - 1 <= N; ++l){
                int r = l + len - 1;
                if(r == N){
                    int val = DP[x - 1][l][r] * qpow(2 , F[x - 2]) % mod;
                    DP[x][l][r] = (DP[x][l][r] + val) % mod;
                }
                else{
                    DP[x][l][r] = (DP[x][l][r] + DP[x - 1][l][r]) % mod;
                }
                if(l == 1){
                    int val = DP[x - 2][l][r] * qpow(2 , F[x - 1]) % mod;
                    DP[x][l][r] = (DP[x][l][r] + val) % mod;
                }
                else{
                    DP[x][l][r] = (DP[x][l][r] + DP[x - 2][l][r]) % mod;
                }
                for(int m = l; m < r; ++m){
                    int val = DP[x - 1][l][m] * DP[x - 2][m + 1][r] % mod;
                    DP[x][l][r] = (DP[x][l][r] + val) % mod;
                }
                if(ID)printf("DP[%d][%d][%d] = %lld\n" , x , l , r , DP[x][l][r]);
            }
        }
    }
    cout << DP[X][1][N] << endl;
}
