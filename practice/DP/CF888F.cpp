#include <bits/stdc++.h>
#define ID if(1)
#define rep(i , a , b) for(int i = a; i <= b; ++i)
using namespace std;
typedef long long ll;
const ll mod = 1e9 + 7;
const int maxn = 505;
int a[maxn][maxn] , N;
ll DP[maxn][maxn][2]; 
// DP[l][r][0] = # ways to connect points[l..r] given that we do not link l to r
// DP[l][r][1] = # ways to connect points[l..r] given that we link l to r
// DP[l][r][0] = #(ways to connect points[l..m] given that we link l to m) * #(ways to connect points[m..r]) * a[l][m]
// DP[l][r][1] = #(ways to connect points[l..m]) * #(ways to connect points[m..r]) * a[l][r]
ll add(ll x , ll y){
    return (x + y) % mod; 
}
ll mul(ll x , ll y){
    return x * y % mod;
}
int main(){
    scanf("%d" , &N);
    rep(i , 1 , N){
        rep(j , 1 , N){
            scanf("%d" , &a[i][j]);
        }
    }
    rep(i , 1 , N)DP[i][i][0] = 1;
    rep(len , 2 , N){
        rep(i , 1 , N - len + 1){
            int j = i + len - 1;
            rep(k , i , j - 1){
                if(a[i][j]){
                    // we can link i to j
                    DP[i][j][1] = add(DP[i][j][1] , mul(add(DP[i][k][0] , DP[i][k][1]) , add(DP[k + 1][j][0] , DP[k + 1][j][1])));
                }
                if(k > i && a[i][k]){
                    // do not link i to j
                    DP[i][j][0] = add(DP[i][j][0] , mul(DP[i][k][1] , add(DP[k][j][0] , DP[k][j][1])));
                }
            }
        }
    }
    printf("%lld\n" , add(DP[1][N][0] , DP[1][N][1]) );
}