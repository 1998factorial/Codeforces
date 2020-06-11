/*
    Dynamic programming (interval)
    DP[l][r] = # of ways to color a[l..r] such that all operations are either completly in side [l..r] or
    outside of [l..r].
    the first color we need to put in [l,r] is the smallest color in [l,r], say it is at position x
    then we can cover x by using interval [a , b] such that x is in [a , b], and [a , b] is a sub interval
    of [l,r]. DP[l][r] = sum of {DP[l][a - 1] * DP[a][x - 1] * DP[x + 1][b] * DP[b + 1][l] for all good a , b}
    notice that the choice of a and b are independent of each other, so we can take the product of both side
    optimize from O(N^4)->O(N^3)
*/
#include <bits/stdc++.h>
using namespace std;
typedef pair<int , int> ii;
typedef long long ll;

const ll mod = 998244353;
ll DP[505][505];
int N , M;
int C[505];

int main(){
    cin >> N >> M;
    for(int i = 1; i <= M; ++i){
        cin >> C[i];
        DP[i][i] = 1;
    }
    for(int i = 1; i <= M + 1; ++i){
        DP[i][i - 1] = 1;
    }
    for(int len = 2; len <= M; ++len){
        for(int i = 1; i + len - 1 <= M; ++i){
            int j = i + len - 1;
            ii e = make_pair(C[i] , i);
            for(int x = i; x <= j; ++x){
                e = min(e , make_pair(C[x] , x));
            }
            int m = e.second;
            /*for(int a = i; a <= m; ++a){
                for(int b = m; b <= j; ++b){
                    ll v = 1;
                    ll v1 = DP[i][a - 1] * DP[a][m - 1] % mod;
                    v = v * v1 % mod;
                    ll v2 = DP[m + 1][b] * DP[b + 1][j] % mod;
                    v = v * v2 % mod;
                    DP[i][j] = (DP[i][j] + v) % mod;
                }
            }*/
            ll l = 0 , r = 0;
            for(int a = i; a <= m; ++a){
                l += DP[i][a - 1] * DP[a][m - 1] % mod;
                l %= mod;
            }
            for(int b = m; b <= j; ++b){
                r += DP[m + 1][b] * DP[b + 1][j] % mod;
                r %= mod;
            }
            DP[i][j] = l * r % mod;
        }
    }
    cout << DP[1][M] << endl;
}
